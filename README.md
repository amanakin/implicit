# Implicit C++ visualization

## Introduction

## Move vs Copy

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
...
{
    VAR_INT(a, 500);
    VAR_INT(b, 1000);

    Int c = AddWithBound(a, b);
}
```

|                       |                                  Move unavailiable                                  |                                                                                Move availiable |                               
|:----------------------|:-----------------------------------------------------------------------------------:|-----------------------------------------------------------------------------------------------:|
| **NRVO unavailiable** | ![](https://github.com/amanakin/implicit/blob/master/examples/no_move_no_nrvo.svg)  |            ![](https://github.com/amanakin/implicit/blob/master/examples/yes_move_no_nrvo.svg) |
| **NRVO availiable**   | ![](https://github.com/amanakin/implicit/blob/master/examples/no_move_yes_nrvo.svg) |           ![](https://github.com/amanakin/implicit/blob/master/examples/yes_move_yes_nrvo.svg) |


