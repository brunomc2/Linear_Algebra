#include "./lib/main.h"

using namespace std;

int main()
{
        cout << "Enter matrix size" << endl;
        int m;
        int n;
        cin >> m;
        cin >> n;
        cout << "Enter the system" << endl;
        L(L(double)) A;
        L(double) b;
        for(int i = 0; i < m; i++)
        {
                for(int j = 0; j < n; j++)
                {
                        cin >> A[i][j];
                }
                cin >> b[i];
        }

        L(double) aprox;
        aprox = least_squares(A,b);

        cout << "Solution: " << endl;
        cout << aprox;
        cout << endl;


        return 0;
}
