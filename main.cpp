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

        // for(int i = 0; i < grades.length(); i++)
        // {
        //         for(int j = 0; j < grades[i].length(); j++)
        //         {
        //                 cout << grades[i][j];
        //                 cout << " ";
        //         }
        //         cout << endl;
        // }
        // cout << endl;

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

        /* ignored_grade
           The minimum average test grade that is needed so that
           your grades are not ignored.
         */
        for(double ignored_grade = 0.0; ignored_grade < 10.0;
            ignored_grade += 0.1)
        {
                /* grades_removed
                   A boolean flag that is activated when, due to
                   the ride of the ignored_grade parameter,
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
                                /* Fallback to consider the first
                                   case, where everyone's grade is
                                   considered.
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

                                // If you removed everything, quit
                                if(grade_averages.length() == 0)
                                {
                                        ignored_grade = 11.0;
                                }
                        }

                        /* If no grade was removed, then increase
                           the threshold.
                         */
                        ignored_grade += 0.1;
                }
                // The number of non-removed students.
                int considered_students = grade_averages.length();

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
                        results[i] = 10.0 - grade_averages[i][1];
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
                        // if(test_weight[0] < 0.0)
                        // {
                        //         test_weight[0] = 0.0;
                        // }
                        // else if(test_weight[0] > 1.0)
                        // {
                        //         test_weight[0] = 1.0;
                        // }


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

                        /* Prints the amount of students in final
                           exam or fails
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
                                if(final_grade <  7.0)
                                {
                                        final_exams++;
                                }
                                else
                                {
                                        approved++;
                                }
                        }
                        // cout << ignored_grade
                             // << " "
                        // Number of fails
                             // << fails
                        // Number of final exams
                             // << final_exams
                        // Number of approved
                             // << approved
                             // << endl;
                }
        }
        cout << endl;

        return 0;
}
