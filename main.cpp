#include <iostream>
#include "Matrix.h"

using namespace std;

void fillMatrix(Matrix& A, int m, int n);

int main()
{
    //Variables
    char keyInput;

    cin >> keyInput;
    switch (keyInput)
    {
        //Addition
        case 'a':
            int m, n;
            cin >> m;
            cin >> n;
            Matrix A(m,n);
            Matrix B(m,n);
            fillMatrix(A, m, n);
            fillMatrix(B, m, n);
            //cout << A << endl;
            cout << A * B << "\n" << endl;
            cout << A + B << "\n" << endl;
            cout << A - B << "\n" << endl;
            cout << A * 4 << "\n" << endl;
            break;
    }
    
}

//Fills a matrix of size M x N based off of standard input stream
void fillMatrix(Matrix& A, int m, int n)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            float val;
            cin >> val;
            A.insertVal(val, i, j);
        }
    }
}