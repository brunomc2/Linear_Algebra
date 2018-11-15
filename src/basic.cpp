/*
   The purpose of this code file is to implement basic functions
   for floating point and vector arithmetic, such as an "almost
   equal" function to compare floating point values and
   linear combination functions.

   Please note that, due to the elementary and widespread use
   of these functions throughout the whole program, a complete
   and descriptive name for the functions will be sacrificed to
   the bare minimum identifiable, such as that they do not
   obfuscate more complex operations in the main code. Since
   they will have straightforward action, it is not expected
   to be a great nuisance.
 */
#include "basic.h"

// Absolute value function
/* SHORT SUMMARY:
   Returns the absolute value of a double x.
 */
double abv(double x)
{
        if(x >= 0)
        {
                return x;
        }
        return -x;
}

// Approximately equal function
/* SHORT SUMMARY:
   Its purpose is to compare, within a tolerance margin of
   epsilon, a small positive constant within the header file,
   if the values of two floating point numbers x and y coincide.
 */
bool aeq(double x, double y)
{
        return (abv(x - y) < control_constants::epsilon);
}

// Linear combination function
/* SHORT SUMMARY:
   A function that does the linear combination of two vectors
   v and w multiplied by the scalars a and b, respectively,
   that is, it does
        av + bw
   note that IT DOES NOT CHECK THE SIZE OF THE VECTORS! It will
   only use the size of the first vector. The nature of the
   linked lists means that empty spaces in the other vectors will
   be assigned a random (memory residual) value.
 */
L(double) lco(double a, L(double) v, double b, L(double) w)
{
        int length = v.length();
        L(double) return_vector;
        for(int i = 0; i < length; i++)
        {
                return_vector[i] = a*v[i] + b*w[i];
        }
        return return_vector;
}

// Matrix-vector multiplication function
/* SHORT SUMMARY:
   This function multiplies a matrix A by a vector v from the
   right, that is, it returns Av. Notive that it DOES NOT CHECK
   THE SIZE of the matrix and vector, considering only the
   size of the matrix as the internal parameter.
 */
L(double) mvm(L(L(double)) A, L(double) v)
{
        /* Notation
           m: Number of lines in the matrix
           n: Number of columns in the matrix, and,
              consequentially, the dimension of the vector.
         */
        int m = A.length();
        int n = A[0].length();
        L(double) return_vector;
        for(int i = 0; i < m; i++)
        {
                return_vector[i] = 0.0;
                for(int j = 0; j < n; j++)
                {
                        return_vector[i] += A[i][j] * v[j];
                }
        }
        return return_vector;
}

// Scalar product funtion
/* SHORT SUMMARY:
   Multiplies each element of a vector by a scalar factor.
 */
L(double) spr(double a, L(double) v)
{
        int len = v.length();
        for(int i = 0; i < len; i++)
        {
                v[i] *= a;
        }
        return v;
}
