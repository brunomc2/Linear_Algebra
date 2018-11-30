#include "./lib/main.h"
#include <iomanip>

using namespace std;

int main()
{
        bool domain_barrier_active = false;
        // Opening the grades file
        ifstream grades_file("./least_squares_data/grades.data");

        // Weights file
        ofstream weights_file("./least_squares_data/"
                              "weights.data");
        // Class average file
        ofstream class_avg_file("./least_squares_data/"
                                "total_class_average.data");
        // Final status file
        ofstream final_status_file("./least_squares_data/"
                                   "final_state.data");

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


        // WEIGHTS
        L(L(double)) grade_matrix = grades;
        L(L(double)) ret_matrix =
        grade_calc(discriminator,
                   grade_matrix,
                   0.0,
                   10.0,
                   0.1);
        int num_weights = ret_matrix[0].length();
        /* Since every line has the ignored grade in it as
        well. */
        num_weights--;
        int num_removals = ret_matrix.length();
        // Domain barrier
        for(int k = 0; k < num_removals &&
                       domain_barrier_active; k++)
        {
                for(int i = 0; i < num_weights; i++)
                {
                        ret_matrix[k][i + 1] =
                        domain_barrier(ret_matrix[k][i + 1]);
                }
        }
        write_to_file(ret_matrix, weights_file);
        weights_file.close();

        // INDIVIDUAL GRADE
        L(L(double)) ind_grade;
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


        // CLASS AVERAGE
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
        write_to_file(class_average, class_avg_file);
        class_avg_file.close();

        // CLASS STATUS
        L(L(double)) class_status;
        /* class_status
            Column 0 for grade threshold,
            Column 1 for approved,
            Column 2 for final exams,
            Column 3 for fails
         */
        for(int k = 0; k < num_removals; k++)
        {
                class_status[k][0] = ret_matrix[k][0];
                class_status[k][1] = 0;
                class_status[k][2] = 0;
                class_status[k][3] = 0;
                for(int i = 0; i < n_students; i++)
                {
                        if(ind_grade[k][i] < 4.0)
                        {
                                class_status[k][3]++;
                        }
                        else if(ind_grade[k][i] < 7.0)
                        {
                                class_status[k][2]++;
                        }
                        else
                        {
                                class_status[k][1]++;
                        }
                }
        }
        write_to_file(class_status, final_status_file);
        weights_file.close();

        return 0;
}
