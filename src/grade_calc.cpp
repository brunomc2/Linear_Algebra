#include "grade_calc.h"
using namespace std;

L(L(double)) grade_calc(L(double)    discriminator,
                        L(L(double)) grade_matrix,
                        double min_grade,
                        double max_grade,
                        double grade_resol)
{
        /* ret_matrix
           Contains, on the first column, the ign_grade value.
           On the subsequent columns, it holds the weights
           configuration for that ignored grade threshold.
         */
        L(L(double)) ret_matrix;

        /* num_removals
           Contains the number of removals, and consequentially,
           the number of lines of ret_matrix.
           Start it at -1 because it counts starting at 0 and
           is incremented everytime it exits the removal loop.
         */
        int num_removals = -1;

        /* The results vector used in the method.
           It is produced by subtracting the
           last column, which contains the score
           from one test/report, from the maximum
           grade.
           The grade differences act as a coefficent
           matrix for the minimum squares method.
         */
        int num_grades = grade_matrix[0].length();
        int num_students = grade_matrix.length();
        L(double) results;
        L(L(double)) grade_differences;
        for(int i = 0; i < num_students; i++)
        {
                // The grade to be removed from the others
                double remove_grade;
                remove_grade = grade_matrix[i][num_grades - 1];

                for(int j = 0; j < num_grades - 1; j++)
                {
                        grade_differences[i][j] =
                        grade_matrix[i][j] -
                        remove_grade;
                }

                results[i] = max_grade - remove_grade;
        }


        /* The discriminator is the number which will be
           compared to a grade which starts at the
           min_grade and goes up to max_grade with intervals of
           grade_resol.
           This grade is called ign_grade, and when it reaches
           the same value as the discriminator, the
           corresponding line of the grade_matrix is removed.
         */
        for(double ign_grade = min_grade;
            ign_grade <= max_grade;
            ign_grade += grade_resol)
        {
                /* grades_removed
                   A boolean flag that is activated when, due
                   to the ignored_grade parameter,
                   some new grade is removed.
                 */
                bool grades_removed = false;
                /* If no grade is removed, then increase the
                   ignored grade threshold.
                 */
                while(!grades_removed)
                {
                        for(int i = 0; i <
                            discriminator.length(); i++)
                        {
                                /* Fallback to catch the
                                   case where no one is
                                   ignored
                                 */
                                if(ign_grade == min_grade)
                                {
                                        grades_removed = true;
                                }

                                /* If the test average is
                                   below the ignored threshold,
                                   then remove it.
                                 */
                                if(discriminator[i] <
                                    ign_grade)
                                {
                                        discriminator.
                                        delete_at(i);
                                        grade_differences.
                                        delete_at(i);
                                        results.
                                        delete_at(i);
                                        i--;
                                        grades_removed = true;
                                }

                                /* If the amount of students
                                   left is smaller than the
                                   amount of grades necessary,
                                   then it means the system
                                   is underdetermined, and
                                   therefore can't be solved
                                   by the minimum squares
                                   method.
                                 */
                                if(discriminator.length() <
                                   grade_differences[0]
                                   .length())
                                {
                                        return
                                        ret_matrix;
                                }
                        }

                        /* If no grade was removed and it
                           still has not reached the limit, then
                           increment the ignored threshold.
                         */
                        if(ign_grade <= max_grade)
                        {
                                ign_grade += 0.1;
                        }
                        else
                        {
                                return ret_matrix;
                        }
                }

                num_removals++;

                /* Add the current ignored grade to the
                   first column of the returning matrix.
                 */
                ret_matrix[num_removals][0] = ign_grade -
                                              grade_resol;

                /* Gets the weights for the current grade
                   configuration.
                 */
                L(double) weights =
                        least_squares(grade_differences,
                                      results);

                ret_matrix[num_removals] += weights;

                /* Adds the weight of the last grade
                 */
                double last_weight = 1.0;
                for(int i = 1; i < num_grades; i++)
                {
                        last_weight -=
                        ret_matrix[num_removals][i];
                }
                ret_matrix[num_removals] += last_weight;
        }

        return ret_matrix;
}
