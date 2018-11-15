/*
   The purpose of this code file is to implement a method of
   Gauss-Jordan elimination to solve linear systems.
   This method will suppose that the system sent in is
   solvable.
 */
#include "gauss_jordan.h"

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
                       L(double)    results)
{
        /*
           This function shall return a column-vector with the
           solutions.
           Therefore, it will start generating pivots.
           After that, it returns cleaning the above rows.
           Finally, it returns the modified results vector,
           which is equivalent, since the matrix is now the
           identity matrix, to the variable values.
         */

        // Receives the size of the system
        int tam = coefficients.length();

        // Reduces the lines with unit pivots
        // For all lines
        for(int i = 0; i < tam; i++)
        {
                /* Permutes the lines, if the pivot candidate
                   is null (or approximately null).
                 */
                if(aeq(coefficients[i][i], 0))
                {
                        for(int j = i + 1; j < tam; j++)
                        {
                                /* If the line below does not
                                   have a null coefficient,
                                   permute with it.
                                 */
                                if(!aeq(coefficients[j][i], 0))
                                {
                                        coefficients.
                                        switch_holds(i, j);
                                        results.
                                        switch_holds(i, j);
                                }
                        }
                }

                /* Turns the current line pivot unitary.
                   First, it is necessary to change the result of
                   the line.
                 */
                results[i] /= coefficients[i][i];
                coefficients[i] = spr(1/coefficients[i][i],
                                      coefficients[i]);

                // For all lines below the current line
                for(int j = i + 1; j < tam; j++)
                {
                        /* This factor is the opposite of the
                           ratio between the first non-null
                           element that is desired to be
                           removed (coefficients[j][i])
                           and the first non-null element of the
                           "cleaning" line. Since, because of the
                           prior phase, the element was turned
                           unitary, it can be then suppressed from
                           the division.
                         */
                        double sum_factor =
                                -1.0 * coefficients[j][i];

                        /* Applies the sum process to the
                           results vector.
                         */
                        results[j] = sum_factor * results[i] +
                                     results[j];

                        /* Applies the reduction linear
                           combination process to the line
                           to be cleaned (coefficients[j]).
                         */
                        coefficients[j] = lco(sum_factor,
                                              coefficients[i],
                                              1,
                                              coefficients[j]);
                }

                std::cout << std::endl;
                for(int r = 0; r < tam; r++)
                {
                        for(int s = 0; s < tam; s++)
                        {
                                std::cout << coefficients[r][s]
                                          << "  ";
                        }
                        std::cout << std::endl;
                }
        }

        // For all lines, starting by the last
        for(int i = tam - 1; i > 0; i--)
        {
                // For all lines above
                for(int j = i - 1; j >= 0; j--)
                {
                        /* Since all pivots are already unitary,
                           it suffices to modify the results
                           vector and put a zero in the i,j
                           position of the coefficients matrix.
                         */
                        double sub_factor;
                        sub_factor = results[i];

                        results[j] -= coefficients[j][i] *
                                      sub_factor;

                        coefficients[j][i] = 0.0;
                }
        }

        return results;
}
