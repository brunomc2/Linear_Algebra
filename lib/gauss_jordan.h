#ifndef GAUSS_JORDAN_H
#define GAUSS_JORDAN_H

#include "basic.h"

// Gauss-Jordan elimination function
/* SHORT SUMMARY:
   The purpose of this function is to solve a linear system
   with the Gauss-Jordan system, in which, through means of
   linear combination of the matrix lines, the coefficient matrix
   is turned into the identity matrix.
   It will receive a coefficient matrix and a result vector,
   returning a variable values vector.
 */
L(double) gauss_jordan(L(L(double)) coefficients,
                       L(double)    results);

#endif // GAUSS_JORDAN_H
