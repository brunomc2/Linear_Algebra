#include "./lib/main.h"

using namespace std;

int main()
{
        // Opening the grades file
        ifstream grades_file("./least_squares_data/grades.data");

        /* grades
           The grades matrix
         */
        L(L(double)) grades;
        /* n_students, n_grades
           n_students: Number of students
           n_grades: Number of grades per student.
        */
        int n_students;
        int n_grades;
        grades_file >> n_students;
        grades_file >> n_grades;

        for(int i = 0; i < n_students; i++)
        {
                // There are 4 grades per person
                for(int j = 0; j < n_grades; j++)
                {
                        grades_file >> grades[i][j];
                }
        }
        grades_file.close();

        /* grade_averages
           A new matrix where the first column is the
           average of the first and last columns of
           grade, and the second is the average of
           the second and third columns. This matrix will be
           progressively pruned in order to consider only grades
           above a certain threshold.
         */
        L(L(double)) grade_averages;
        for(int i = 0; i < n_students; i++)
        {
                grade_averages[i][0] =
                        0.5 * (grades[i][0] +
                               grades[i][3]);
                grade_averages[i][1] =
                        0.5 * (grades[i][1] +
                               grades[i][2]);
        }
        /* grade_averages_copy
           An unmodified copy of the grade averages so that, at
           the end, you can compute the whole class average grade.
         */
        L(L(double)) grade_averages_copy = grade_averages;

        /* This first treatment will consider the first and last
           grades, which correspond to test grades, together.
           The same applies to the second and third grades,
           which are report grades.
           Thus. the least square methods will consider their
           simple average. Therefore, since the way done will
           adjust their weights such as that their sum adds up
           to one, we only trully have one variable: since the
           final grade is, if T is the test grades, R is the
           reports grades, W1 the test weight and W2 the
           reports weight, the final grade F is
                F = (W1*T + W2*R)/(W1 + W2)
           If we force W1 + W2 = 1, we have
                F = W1*T + (1 - W1)*R
                  = R + W1*(T - R)
                F - R = W1*(T - R)
           We want all students to have grade 10, so we will
           have to do a simple minimum square, considering we
           trully have one variable.
                10 - R = W1*(T - R)
         */
        /* ignored_grade
           The minimum average test grade that is needed so that
           your grades are not ignored.
         */
        for(double ignored_grade = 0.0; ignored_grade < 10.0;
            ignored_grade += 0.1)
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
                            grade_averages.length(); i++)
                        {
                                /* Fallback to consider the
                                   first
                                   case, where everyone's grade
                                   is considered.
                                 */
                                if(aeq(ignored_grade, 0.0))
                                {
                                        grades_removed = true;
                                }

                                /* If the test average is
                                   below the ignored threshold,
                                   then remove it.
                                 */
                                if(grade_averages[i][0] <
                                   ignored_grade)
                                {
                                        grade_averages.
                                        delete_at(i);
                                        i--;
                                        grades_removed = true;
                                }

                                /* If you removed everything,
                                   quit
                                 */
                                if(grade_averages.length() == 0)
                                {
                                        ignored_grade = 11.0;
                                }
                        }

                        /* If no grade was removed, then
                           increase the threshold.
                         */
                        ignored_grade += 0.1;
                }
                // The number of non-removed students.
                int considered_students =
                     grade_averages.length();

                /* grade_difference
                   A mx1 matrix that contains the
                   difference between the (T) test grade average
                   and the (R) report grade average.
                 */
                L(L(double)) grade_difference;
                for(int i = 0; i < considered_students; i++)
                {
                        grade_difference[i][0] =
                                grade_averages[i][0] -
                                grade_averages[i][1];
                }
                /* results
                   The results vector, given by the difference
                   between 10 and the reports average
                   grade (10 - R);
                 */
                L(double) results;
                for(int i = 0; i < considered_students; i++)
                {
                        results[i] = 10.0 -
                                     grade_averages[i][1];
                }
                /* test_weight
                   A 1x1 vector that contains the test weight.
                 */
                // Only act if there are students left.
                if(considered_students != 0)
                {
                        L(double) test_weight =
                                least_squares(grade_difference,
                                              results);
                        /* Applies a "domain barrier", which
                           rounds negative weights to 0 and
                           weights above 1 to 1.
                         */
                        if(test_weight[0] < 0.0)
                        {
                                test_weight[0] = 0.0;
                        }
                        else if(test_weight[0] > 1.0)
                        {
                                test_weight[0] = 1.0;
                        }


                        /* Print the test average weight as a
                           function of the ignored grade.
                         */
                        // cout << ignored_grade
                        //      << " ";
                        // cout << test_weight[0];
                        // cout << endl;

                        /* Print the reports average weight as
                           a function of the ignored grade.
                        */
                        // cout << ignored_grade
                        //      << " ";
                        // cout << 1 - test_weight[0];
                        // cout << endl;

                        /* Print the average class final
                           grade as a function of the ignored
                           grade.
                         */
                        // double total_average = 0.0;
                        // for(int i = 0; i < n_students;
                        //     i++)
                        // {
                        //         total_average +=
                        //         test_weight[0] *
                        //         grade_averages_copy[i][0]
                        //         + (1 - test_weight[0]) *
                        //         grade_averages_copy[i][1];
                        // }
                        // total_average /= n_students;
                        // cout << ignored_grade
                        //      << " ";
                        // cout << total_average;
                        // cout << endl;

                        /* Prints the amount of students in
                           final exam or fails
                         */
                        int final_exams = 0;
                        int fails = 0;
                        int approved = 0;
                        for(int i = 0; i < n_students;
                            i++)
                        {
                                double final_grade =
                                test_weight[0] *
                                grade_averages_copy[i][0]
                                + (1 - test_weight[0]) *
                                grade_averages_copy[i][1];

                                if(final_grade < 4.0)
                                {
                                        fails++;
                                }
                                else if(final_grade <  7.0)
                                {
                                        final_exams++;
                                }
                                else
                                {
                                        approved++;
                                }
                        }
                        cout << ignored_grade - 0.1
                             << " "
                        // Number of fails
                             << fails
                        // Number of final exams
                             // << final_exams
                        // Number of approved
                             // << approved
                             << endl;
                }
        }
        cout << endl;

        /* This second case consider independent weights for
           each one of the grades. If each student has two
           test grades T1 and T2, and two report grades
           R1 and R2, all with weights W1, W2, W3 and W4,
           respectively, then their final grande F is given
           by
                F = (W1*T1 + W2*T2 + W3*R1 + W4*R2) /
                    (W1 + W2 + W3 + W4)
           If, as in the prior case, we force W1 + W2 + W3 + W4
           = 1, then we can write the grade as
                F = W1*T1 + W2*T2 + W3*R1 +
                    (1 - W1 - W2 - W3)*R2
                  = W1*(T1 - R2) + W2*(T2 - R2)
                    + W3*(R1 - R2) + R2
           Since the derired result is for all students to have
           grade 10.0, it can be written as a minimum square
           problem of the form
                10 - R2 = W1*(T1 - R2) + W2*(T2 - R2)
                          + W3*(R1 - R2)
         */
        /* grade_difference
           A matrix which contains the (T1 - R2), (T2 - R2) and
           (R1 - R2) columns. It will work as the matrix of
           coefficients in the least square method. Since this
           matrix will be reduced based on the grade threshold,
           a copy will be made to calculate the final grades.
         */
         /* results
           This vector will contain the difference between 10 and
           the grade of the last report (10 - R2). This vector will
           be used as the result vector in the least square
           method.
          */
        // L(L(double)) grade_difference;
        // L(double)    results;
        // for(int i = 0; i < n_students; i++)
        // {
        //         for(int j = 0; j < n_grades - 1; j++)
        //         {
        //                 grade_difference[i][j] =
        //                         grades[i][j] -
        //                         grades[i][n_grades];
        //                 results[i] = 10.0 - grades[i][n_grades];
        //         }
        // }
        //
        // // Grade threshold
        // bool insufficient_matrix = false;
        //  /* If no grade is removed, then increase the
        //     ignored grade threshold.
        //   */
        // for(double ignored_grade = 0.0; ignored_grade < 10.0 &&
        //                                 !insufficient_matrix;
        //     ignored_grade += 0.1)
        // {
        //         /* grades_removed
        //             A boolean flag that is activated when, due
        //             to the ignored_grade parameter,
        //             some new grade is removed.
        //           */
        //         bool grades_removed = false;
        //         /* insufficient_matrix
        //            A boolean flag that is activated when the
        //            matrix of coefficients is too small (less)
        //            then n_grades - 1.
        //          */
        //
        //         while(!grades_removed)
        //         {
        //                 for(int i = 0; i <
        //                     grade_averages.length(); i++)
        //                 {
        //                         /* Fallback to consider the
        //                            first
        //                            case, where everyone's grade
        //                            is considered.
        //                          */
        //                         if(aeq(ignored_grade, 0.0))
        //                         {
        //                                 grades_removed = true;
        //                         }
        //
        //                         /* If the test average is
        //                            below the ignored threshold,
        //                            then remove it.
        //                          */
        //                         if(grade_averages[i][0] <
        //                            ignored_grade)
        //                         {
        //                                 /* Delete the average,
        //                                    so that it is no
        //                                    longer compared in the
        //                                    next run, and
        //                                    delete all the four
        //                                    grades as well,
        //                                    so that it does
        //                                    not count for the
        //                                    linear regression.
        //                                    Also remove that line
        //                                    in the results vector.
        //                                  */
        //                                 grade_averages.
        //                                 delete_at(i);
        //                                 grade_difference.
        //                                 delete_at(i);
        //                                 results.
        //                                 delete_at(i);
        //                                 i--;
        //                                 grades_removed = true;
        //                         }
        //
        //                         /* If there are less then 3
        //                            students, quit
        //                          */
        //                         if(grade_averages.length() < 3)
        //                         {
        //                                 insufficient_matrix = true;
        //                                 grades_removed = true;
        //                         }
        //                 }
        //
        //                 /* If no grade was removed, then
        //                    increase the threshold.
        //                  */
        //                 ignored_grade += 0.1;
        //         }
        //
        //         L(double) weights;
        //         if(!insufficient_matrix)
        //         {
        //                 weights = least_squares(grade_difference,
        //                                 results);
        //
        //                 /* Prints the weigths as a function of the
        //                    grade threshold.
        //                  */
        //                 // cout << ignored_grade - 0.1 << " ";
        //                 // Print W1
        //                 // cout << weights[0]
        //                 //      << endl;
        //                 // Print W2
        //                 // cout << weights[1]
        //                 //      << endl;
        //                 // Print W3
        //                 // cout << weights[2]
        //                 //      << endl;
        //                 // Print W4
        //                 // cout << 1 -weights[0]
        //                 //         -weights[1] -weights[2]
        //                 //      << endl;
        //
        //                 /* Prints the average grade of the
        //                    class as a
        //                    function of the grade threshold.
        //                  */
        //                 // double total_average = 0.0;
        //                 // for(int i = 0; i < n_students; i++)
        //                 // {
        //                 //         total_average +=
        //                 //         weights[0] * grades[i][0] +
        //                 //         weights[1] * grades[i][1] +
        //                 //         weights[2] * grades[i][2] +
        //                 //         (1 - weights[0]
        //                 //            - weights[1]
        //                 //            - weights[2]) * grades[i][3];
        //                 // }
        //                 // total_average /= n_students;
        //                 // cout << ignored_grade - 0.1 << " ";
        //                 // cout << total_average << endl;
        //
        //                 /* Plot the number of people who are
        //                    approved, failed or are in final
        //                    exam.
        //                  */
        //                 int approved = 0;
        //                 int fails = 0;
        //                 int final_exams = 0;
        //                 double final_grade = 0.0;
        //                 for(int i = 0; i < n_students; i++)
        //                 {
        //                         final_grade =
        //                         weights[0] * grades[i][0] +
        //                         weights[1] * grades[i][1] +
        //                         weights[2] * grades[i][2] +
        //                         (1 - weights[0]
        //                            - weights[1]
        //                            - weights[2]) * grades[i][3];
        //
        //                         if(final_grade < 4.0)
        //                         {
        //                                 fails++;
        //                         }
        //                         else if(final_grade < 7.0)
        //                         {
        //                                 final_exams++;
        //                         }
        //                         else
        //                         {
        //                                 approved++;
        //                         }
        //                 }
        //                 cout << ignored_grade - 0.1 << " ";
        //                 // cout << approved << endl;
        //                 // cout << fails << endl;
        //                 cout << final_exams << endl;
        //         }
        // }


        return 0;
}
