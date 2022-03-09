# Implicit C++ visualization

## Introduction

Rvalue references are a feature of C++ that was added with the C++11 standard.
Why was such a design needed and how to work with it correctly?

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
You can read about it [here](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2027.html#Move_Semantics).

Here you see sample code of function *AddWithBound*:

```c++
#define VAR_INT(name, ...) \
    Int name((#name), ##__VA_ARGS__)

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

## std::move

However, here the call to std::move precludes the NRVO,
because it breaks the conditions specified in the C++ standard,
namely : the returned expression must be a name. 
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
That is, you should not write *std::move* always.

## Conclusion

Always think about what you write when programming in C++.

### References
* [Move_Semantics](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2027.html#Move_Semantics)
* [Perfect Forwarding](https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c)