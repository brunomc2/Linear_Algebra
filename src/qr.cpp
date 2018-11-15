/* This code file has the purpose of implementing the QR
   decomposition. This shall be done using rotations.
 */
#include "qr.h"

// QR decomposition function
/* SHORT SUMMARY:
   This function returns a vector containing two matrices:
   In the first position, the Q matrix, in the second, the
   second position.
   The function will receive a matrix A
 */
L(L(L(double))) qr(L(L(double)) A)
{
        /* The way this function will operate will be:
                1. Calculate one of the transposed rotations;
                2. This function will be used to clean the
                   lines below and also will multiply the
                   previous transposed rotations;
                3. In the case of the first rotation, the
                   matrix will multiply the identity matrix;
                4. Notice that, to save up time, we will use
                   the operation which the matrix encodes
                   rather than the actual operation.
         */
        /* Notation
           The notation used will be:
                * m: The number of lines of the A matrix;
                * n: The number of columns of the A matrix;
         */
        int m = A.length();
        int n = A[0].length();

        /* absorb_matrix
           The absorb_matrix is a mxm matrix that starts as the
           identity matrix, and receives the left-multiplication
           of the transposed rotation matrices. By the end of
           the process, this matrix will be the transpose of
           the Q matrix.
         */
        L(L(double)) absorb_matrix;
        for(int i = 0; i < m; i++)
        {
                for(int j = 0; j < m; j++)
                {
                        if(i == j)
                        {
                                absorb_matrix[i][j] = 1.0;
                        }
                        else
                        {
                                absorb_matrix[i][j] = 0.0;
                        }
                }
        }

        // For all columns
        for(int j = 0; j < n; j++)
        {
                // For all positions below the main diagonal
                for(int i = j + 1; i < m; i++)
                {
                        /* x
                           The entry of the matrix that is not
                           desired to be eliminated.
                         */
                        double x = A[j][j];

                        /* y
                           The entry of the matrix that is
                           desired to be nulled.
                         */
                        double y = A[i][j];

                        /* r
                           The square root of the sum of the
                           squares of x and y
                         */
                        double r = sqrt(x*x + y*y);

                        /* c
                           Cossine of the angle. Used in the
                           rotation matrix.
                         */
                        double c = x / r;

                        /* s
                           The sine of the angle.
                         */
                        double s = y / r;

                        /* These parameters are all you need
                           to define the rotation matrix.
                         */
                        /* keep_line
                           Line that is meant to be kept, that is,
                           the line with the pivot.
                         */
                        L(double) keep_line = A[j];

                        /* move_line
                           Line that is meant to be changed, that
                           is, the line with the element meant
                           to be nulled.
                         */
                        L(double) move_line = A[i];

                        /* Applies the action codified by the
                           rotation matrix to A matrix.
                         */
                        A[j] = lco(c, keep_line,
                                   s, move_line);
                        A[i] = lco(-s, keep_line,
                                    c, move_line);

                        /* Now applies the same action to the
                           absorbing matrix.
                         */
                        keep_line = absorb_matrix[j];
                        move_line = absorb_matrix[i];
                        absorb_matrix[j] = lco(c, keep_line,
                                               s, move_line);
                        absorb_matrix[i] = lco(-s, keep_line,
                                                c, move_line);
                }
        }

        /* Now transpose the absorb_matrix to obtain the
           Q matrix. This will be done inside the return vector.
         */
        L(L(L(double))) return_vector;
        for(int i = 0; i < m; i++)
        {
                for(int j = 0; j < m; j++)
                {
                        return_vector[0][i][j] =
                        absorb_matrix[j][i];
                }
        }
        return_vector[1] = A;

        return return_vector;
}
