#ifndef GRADE_CALC_H
#define GRADE_CALC_H

#include "basic.h"
#include "gauss_jordan.h"
#include "qr.h"
#include "least_squares.h"
#include <iostream>
#include <fstream>

/* This file will house the functions which calculate the
   weights as a function of the ignored grade.
 */
L(L(double)) grade_calc(L(double)    discriminator,
                        L(L(double)) grade_matrix,
                        double       min_grade,
                        double       max_grade,
                        double       grade_resol);

/* This function writes a matrix to a file.
 */
void write_to_file(L(L(double)) matrix, std::ofstream& file);

/* Forces the weigth into the [0,1] range
 */
double domain_barrier(double weigth);

#endif // GRADE_CALC_H
