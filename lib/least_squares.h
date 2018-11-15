#ifndef LEAST_SQUARES_H
#define LEAST_SQUARES_H

// #include "basic.h"
#include "qr.h"
#include "gauss_jordan.h"

// Least squares function
/* SHORT SUMMARY:
   This function will receive a coefficients matrix A and a results
   vector b which will be the approximation goal.
   The return will be the x vector from the least square
   problem
        min{Ax - b}
 */
L(double) least_squares(L(L(double)) A, L(double) b);

#endif
