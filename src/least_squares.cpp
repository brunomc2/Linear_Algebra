/* This code file has the purpose of implementing the least
   square method for maximizing linear systems. This will be done
   using the QR decomposition.
 */
#include "least_squares.h"

// Least squares function
/* SHORT SUMMARY:
   This function will receive a coefficients matrix A and a results
   vector b which will be the approximation goal.
   The return will be the x vector from the least square
   problem
        min{Ax - b}
 */
L(double) least_squares(L(L(double)) A, L(double) b)
{
        /* Notation
           m: The number of lines of the matrix;
           n: The number of columns of the matrix;
           To apply correctly this method, it is supposed that
           m >= n.
         */
        int m = A.length();
        int n = A[0].length();

        /* The way this function will work is:
                1. Calculate the QR decomposition of the
                   A matrix;
                2. Drop the last (m - n) lines of the transpose
                   of Q and the R matrices.
                   Since the QR decomposition returns Q and R,
                   with the Q matrix, and it needs to be
                   transposed, it will be transposed while
                   ignoring the last (m - n) columns (which
                   makes the Q transpose a nxm matrix).
                3. The reduced system, with the nxn matrix that
                   came from the top of the R matrix, and the
                   Q-transpose-b product will be solved by the
                   Gauss-Jordan system.
         */
        L(L(L(double))) qr_decomposition = qr(A);

        /* qtr
           qtr stands for Q Transpose Reduced, that means the
           Q matrix transposed with its last (m - n) lines
           removed, making it a mxn matrix.
         */
        L(L(double)) qtr;
        for(int i = 0; i < m; i++)
        {
                for(int j = 0; j < n; j++)
                {
                        qtr[j][i] = qr_decomposition[0][i][j];
                }
        }

        /* rr
           rr stands for R Reduced, that means the R matrix with
           its last (m - n) lines removed, making it a nxn
           upper triangle matrix.
         */
        L(L(double)) rr;
        for(int i = 0; i < n; i++)
        {
                rr[i] = qr_decomposition[1][i];
        }

        /* Now it is necessary to solve for x in the system
                rr x = qtr b
           The qtr b product will be done by the mvm function.
         */
        b = mvm(qtr, b);

        /* x
           The solution for the minimizing problem
         */
        L(double) x = gauss_jordan(rr, b);

        return x;
}
