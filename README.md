# C++ rvalue references and perfect forwarding with visual examples 

## Introduction

Rvalue references are a feature of C++ that was added with the C++11 standard.
Why was such a design needed and how to work with it correctly?

### Analysis

C++ has a lot of implicit calls and optimizations, because of this,
the actual execution of the program can be a mystery even for experienced programmers.
Therefore, for clarity, I will use a ``Int class`` with overloaded methods 
that show a program execution as a graph.

Implementation of ``Int class``:
```c++
struct Int {
    Int();
    explicit Int(const std::string& name);
    Int(const std::string& name, int64_t value);
    Int(int64_t value); // allow implicit conversions

    explicit operator int64_t() const;

    Int(const Int& other);
    Int(const std::string& name, const Int& other);
    Int& operator=(const Int& other);

    Int& operator++();
    Int  operator++(int);
    Int& operator--();
    Int  operator--(int);
private:
    // ...
}

Int operator+(const Int& lhs, const Int& rhs);
Int operator-(const Int& lhs, const Int& rhs);
Int operator*(const Int& lhs, const Int& rhs);
Int operator/(const Int& lhs, const Int& rhs);
Int operator%(const Int& lhs, const Int& rhs);

Int& operator+=(Int& lhs, const Int& rhs);
Int& operator-=(Int& lhs, const Int& rhs);
Int& operator*=(Int& lhs, const Int& rhs);
Int& operator/=(Int& lhs, const Int& rhs);
Int& operator%=(Int& lhs, const Int& rhs);

bool operator==(const Int& lhs, const Int& rhs);
bool operator!=(const Int& lhs, const Int& rhs);
bool operator<=(const Int& lhs, const Int& rhs);
bool operator>=(const Int& lhs, const Int& rhs);
bool operator< (const Int& lhs, const Int& rhs);
bool operator> (const Int& lhs, const Int& rhs);
```

Some constructors contain an obscure `name` parameter.
This is necessary for a convenient graph layout,
on which the names of the variables and the actions that occur with them will be demonstrative.

For use in the code, a **VAR_INT** macro is used:
```c++
#define VAR_INT(name, ...) \
    Int name((#name), ##__VA_ARGS__)
```

## Move vs Copy

One of the problems with C++ was copying. 
To deal with this, **RVO** and **NRVO** optimizations were invented.
When returning a local variable of the same class type as the function return type, the compiler is free to omit any copying or moving (i.e., perform copy/move elision), if the variable we are returning is a non-volatile automatic object and is not a function parameter. 
In such a case, the compiler can construct the object directly in its final destination (i.e., in the caller's stack frame).
The compiler is free to perform this optimization even when the move/copy construction has side effects.
Additionally, C++17 says that copy elision is mandatory in certain situations.
This is what we call Named Return Value Optimization (NRVO).

But in the C++11 standard, a much more powerful tool was introduced that allows 
you to get rid of unnecessary copying at the OOP level - **Move semantics**. 
Rvalue references and move semantics are strongly related, and this is very broad topic,
you can read about it [here](https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html#:~:text=Move%20semantics%20allows%20you%20to,object%20and%20used%20by%20another.). 

Here you see sample code of function *AddWithBound*:

```c++
Int AddWithBound(const Int& a, const Int& b) {
    VAR_INT(res, a + b);
    if (res > 1000) {
        res = 1000;
    } else if (res < 0) {
        res = 0;
    }

    return res;
}

// ...

{
    VAR_INT(a, 500);
    VAR_INT(b, 1000);

    Int c = AddWithBound(a, b);
}
```

And here you can see calls of *Int* class methods. 
Red blocks - object copying, green - moving. 

|                       |                                  Move unavailiable                                  |                                                                                Move availiable |                               
|:----------------------|:-----------------------------------------------------------------------------------:|-----------------------------------------------------------------------------------------------:|
| **NRVO unavailiable** | ![](https://github.com/amanakin/implicit/blob/master/examples/no_move_no_nrvo.svg)  |            ![](https://github.com/amanakin/implicit/blob/master/examples/yes_move_no_nrvo.svg) |
| **NRVO availiable**   | ![](https://github.com/amanakin/implicit/blob/master/examples/no_move_yes_nrvo.svg) |           ![](https://github.com/amanakin/implicit/blob/master/examples/yes_move_yes_nrvo.svg) |

As can be seen from the examples, with the optimization the number of unnecessary calls is reduced.
Also, with heavy classes that have a move constructor much faster than a copy constructor,
it will be clear how important it is to keep track of implicit calls in C++.

## Manual moving

Sometimes you need to explicitly show
that an object is to be moved rather than copied.
For example - unique_ptr, file streams, and other structures with only
one owner. To solve this problem, it is enough to make a ``static_cast``
to rvalue reference.
There is a convenient wrapper for this - `std::move`:
```c++
template <class T>
remove_reference<T>&& move(T&& t) noexcept {
    return static_cast<remove_reference<T>&&>(t);
}
```

However, the call to ``std::move`` precludes the NRVO,
because it breaks the conditions specified in the C++ standard,
namely: the returned expression must be a name. 
The reason for this is that std::move returns a reference, and in general, the compiler can't know to what object the function returns a reference to.

So if we change our function *AddWithBound* code to the following:
```c++
Int AddWithBound(const Int& a, const Int& b) {
    VAR_INT(res, a + b);
    if (res > 1000) {
        res = 1000;
    } else if (res < 0) {
        res = 0;
    }

    return std::move(res);
}
```

We well get this:
![](https://github.com/amanakin/implicit/blob/master/examples/yes_move_yes_nrvo_bad_move.svg)
The example was going with Move and RNVO.
It can be seen that the RNVO didn't really work.
That is, you should not write ``std::move`` always.

## Perfect forwarding

### Old solution

Let's imagine that we have a class ``Pair``, 
which contains two objects of different types. 
Then what should the constructor of such a class look like?
In C++98, we would have written code like this:
```c++
template <typename Tl, typename Tr>
struct Pair {
    Pair(const Tl& lhs, const Tr& rhs) :
        lhs_(lhs), rhs_(rhs)
    {}
    // ...

private:
    Tl lhs_;
    Tr rhs_;
};
```

And to dump, the constructor will be called like this:
```c++
{
    VAR_INT(a, 42);
    Pair<Int, Int> mystic_pair(a, Int(12));
}
```

And this is how the dump of our code looks like in the current implementation.
As you can see, we are copying data from temporary object `Int(12)`.
We would like to avoid this.
![](https://github.com/amanakin/implicit/blob/master/examples/bad_pair.svg)

### Move solution
Now we know that we can improve the constructor
with move semantics, 
since now we are copying objects from
the constructor parameters to the class fields.

```c++
template <typename Tl, typename Tr>
struct Pair {
    Pair(Tl lhs, Tr rhs) :
        lhs_(std::move(lhs)), rhs_(std::move(rhs))
    {}
    // ...

private:
    Tl lhs_;
    Tr rhs_;
};
```

Now we have to copy lvalue into the constructor itself,
and only THEN the local object is moved into the class field.
This is much better, but I would like to avoid unnecessary move constructor.
![](https://github.com/amanakin/implicit/blob/master/examples/bad_pair_move.svg)

### Overloading

We want rvalue parameter to only be moved and lvalue parameter to be only copied.
Then let's consider all possible cases of the location of parameters in the constructor.
So the solution is:
```c++
template <typename Tl, typename Tr>
struct Pair {
    Pair(const Tl& lhs, const Tr& rhs) :
        lhs_(lhs), rhs_(rhs)
    {}
    Pair(const Tl& lhs, Tr&& rhs) :
            lhs_(lhs), rhs_(std::move(rhs))
    {}
    Pair(Tl&& lhs, const Tr& rhs) :
            lhs_(std::move(lhs)), rhs_(rhs)
    {}
    Pair(Tl&& lhs, Tr&& rhs) :
        lhs_(std::move(lhs)), rhs_(std::move(rhs))
    {}

private:
    Tl lhs_;
    Tr rhs_;
};
```

But obviously it's not possible to write code this way.
We need some other simpler, but no less effective solution.
![](https://github.com/amanakin/implicit/blob/master/examples/bad_pair_together.svg)

### Perfect forwarding

We want a pretty wrapper around static_cast<T&&>(t)
when T can be deduced to either U& or U&&,
depending on the kind of argument to the wrapper (lvalue or rvalue).
This wrapper is called `forward`. 
Forward is almost always used in conjunction with universal references.
You can read more about it this in this article:
[Perfect forwarding and universal references in C++ by Eli Bendersky](https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c).
Here I will give simple implementation of the `forward`:
```c++
template <typename T>
T forward(typename remove_reference<T>& t) noexcept {
    return static_cast<T&&>(t);
}
```

With the perfect forward and universal references,
we can rewrite `Pair` code like this. 
```c++
template <typename Tl, typename Tr>
struct Pair {
    template <typename Ul, typename Ur>
    Pair(Ul&& lhs, Ur&& rhs) :
        lhs_(std::forward<Ul>(lhs)), rhs_(std::forward<Ur>(rhs))
    {}

private:
    Tl lhs_;
    Tr rhs_;
};
```

As a result, we get a simple and effective solution to our problem.
![](https://github.com/amanakin/implicit/blob/master/examples/good_pair.svg)

## Conclusion

In C++11 added rvalue reference, move, perfect_forwarding, and a lot more.
As you can see, it is very important to understand how the code you write works
and apply new features only where needed.

### References
* [References and move in C++ by Alex Allain](https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html#:%7E:text=Move%20semantics%20allows%20you%20to,object%20and%20used%20by%20another.)
* [Move semantics and rvalue reference by Bjarne Stroustrup](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2027.html#Move_Semantics)
* [Perfect forwarding and universal references in C++ by Eli Bendersky](https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c)