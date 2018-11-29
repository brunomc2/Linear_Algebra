#include "./lib/main.h"
#include <iomanip>

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
        L(double) discriminator;
        for(int i = 0; i < n_students; i++)
        {
                discriminator[i] =
                grade_averages[i][0] =
                        0.5 * (grades[i][0] +
                               grades[i][3]);
                grade_averages[i][1] =
                        0.5 * (grades[i][1] +
                               grades[i][2]);
        }


        L(L(double)) grade_matrix = grade_averages;
        L(L(double)) ret_matrix =
        grade_calc(discriminator,
                   grade_matrix,
                   0.0,
                   10.0,
                   0.1);

        // Individual grade
        L(L(double)) ind_grade;
        int num_weights = ret_matrix[0].length();
        /* Since every line has the ignored grade in it as
           well.
         */
        num_weights--;
        int num_removals = ret_matrix.length();

        // For all weight configurations
        for(int k = 0; k < num_removals; k++)
        {
                for(int i = 0; i < n_students; i++)
                {
                        ind_grade[k][i] = 0.0;
                        for(int j = 0; j < num_weights; j++)
                        {
                                ind_grade[k][i] +=
                                grade_matrix[i][j] *
                                ret_matrix[k][j + 1];
                        }
                }
        }

        L(L(double)) class_average;
        // For all weight configurations
        for(int k = 0; k < num_removals; k++)
        {
                // Get the cut grade
                class_average[k][0] = ret_matrix[k][0];
                class_average[k][1] = 0.0;

                // Sum up and average all students grades
                for(int i = 0; i < n_students; i++)
                {
                        class_average[k][1] +=
                        ind_grade[k][i];
                }

                class_average[k][1] /= n_students;
        }

        for(int i = 0; i < class_average.length(); i++)
        {
                cout << class_average[i][0];
                cout << " ";
                cout << class_average[i][1];
                cout << endl;
        }

        return 0;
}
