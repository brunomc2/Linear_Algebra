#include "./lib/main.h"

using namespace std;

int main()
{
        cout << "Enter matrix size" << endl;
        int size;
        cin >> size;
        cout << "Enter the matrix" << endl;
        L(L(double)) A;
        for(int i = 0; i < size; i++)
        {
                for(int j = 0; j < size; j++)
                {
                        cin >> A[i][j];
                }
        }

        L(L(L(double))) qr_decomposition = qr(A);

        cout << endl
             << "QR decomposition"
             << endl;
        cout << "Q: " << endl;
        for(int i = 0; i < A.length(); i++)
        {
                for(int j = 0; j < A.length(); j++)
                {
                        cout << qr_decomposition[0][i][j];
                        cout << " ";
                }
                cout << endl;
        }
        cout << endl;
        cout << "R: " << endl;
        for(int i = 0; i < A.length(); i++)
        {
                for(int j = 0; j < A[0].length(); j++)
                {
                        cout << qr_decomposition[1][i][j];
                        cout << " ";
                }
                cout << endl;
        }

        return 0;
}
