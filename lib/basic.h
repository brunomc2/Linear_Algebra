#ifndef BASIC_H
#define BASIC_H

#include "../Linked_Lists/lists.h"

namespace control_constants
{
        // Used for precision margins
        static const double epsilon = 0.00001;
};


// Absolute value function
/* SHORT SUMMARY:
   Returns the absolute value of a double x.
 */
double abv(double x);
// Approximately equal function
/* SHORT SUMMARY:
   Its purpose is to compare, within a tolerance margin of
   epsilon, a small positive constant within the header file,
   if the values of two floating point numbers x and y coincide.
 */
bool aeq(double x, double y);
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
L(double) lco(double a, L(double) v, double b, L(double) w);
// Scalar product funtion
/* SHORT SUMMARY:
   Multiplies each element of a vector by a scalar factor.
 */
L(double) spr(double a, L(double) v);


#endif // BASIC_H
