#include <cmath>
#include <iostream>

#include "hw04.h"

// Pre-conditions: none
// Post-conditions: none
//
//          e.g. x=4, y=0 -> 1
//               x=4, y=1 -> 4
//               x=4, y=2 -> 16
//               x=4, y=3 -> 64/ Returns: returns the pow of x**y (aka x^y, x
//               raised to the y)
unsigned int int_pow(unsigned int x, unsigned int y) {
    int z = 1;
    for (int i = 0; i < y; i++) {
        z *= x;
    }
    return z;
}

// Pre-conditions: none
// Post-conditions: none
// Returns: returns the sum of the numbers between [0, .. n]
//
//          if n == 11, the range would be
//              0,1,2,3,4,5,6,7,8,9,10
//
//          And then, you would return the sum of that sequence mentioned above:
//              0+1+2+3+4+5+6+7+8+9+10 -> 55
unsigned int range_sum(unsigned int n) {
    uint sum = 0;
    for (int i = 1; i < n; i++) {
        sum += i;
    }
    return sum;
}

// Pre-conditions: none
// Post-conditions: none
// Returns: returns the nth number in the fibonacci sequence
//
//          The fibonacci sequence is defined as:
//              fib(0) = 0
//              fib(1) = 1
//              fib(n) = fib(n-2) + fib(n+1)
//          For example, the sequence would look like:
//              0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ...
unsigned int fibonacci(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    uint nmin2 = 0;
    uint nmin1 = 1;
    for (int i = 1; i < n; i++) {
        int temp = nmin2;
        nmin2 = nmin1;
        nmin1 = temp + nmin2;
    }
    return nmin1;
}

// Pre-conditions: input will be >= 0.0
// Post-conditions: none
// Returns: returns the cubic root of input calculated via bisection
//
//          Use the bisection algorithm to reduce the guessing space
//          window of where the potential answer could be located at
//
//          if the input is 25, a valid initial window would be [0, 25]
//
//          do note that numbers between [0,1] are a bit special, so think
//          about reasonable windows for those items
//
//          the return value must be within 0.001 of the real answer
//
//          also, the fabs function may be useful for you (floating point
//          absolute value)
//
double bisect_cubicroot(double input) {
    const double ERROR = 0.001;
    double upper = (input < 1) ? 1 : input;
    double lower = 0;
    double midpoint;
    while (upper > lower + ERROR) {
        midpoint = (upper + lower) / 2;
        if (midpoint * midpoint * midpoint > input) {
            upper = midpoint;
        }
        else {
            lower = midpoint;
        }
    }
    return midpoint;
}
