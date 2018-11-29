#ifndef GRADE_CALC_H
#define GRADE_CALC_H

#include "basic.h"
#include "gauss_jordan.h"
#include "qr.h"
#include "least_squares.h"
#include <iostream>

/* This file will house the functions which calculate the
   weights as a function of the ignored grade.
 */
L(L(double)) grade_calc(L(double)    discriminator,
                        L(L(double)) grade_matrix,
                        double       min_grade,
                        double       max_grade,
                        double       grade_resol);

#endif // GRADE_CALC_H
