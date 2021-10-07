#include <iostream>
#include "Matrix.h"

using namespace std;

Matrix& fillMatrix(int m, int n);

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
            A = fillMatrix(m,n);
            //fillMatrix(m,n);
            //cout << (A + B) << endl;
            break;
    }
    
}

//Fills a matrix of size M x N based off of standard input stream
Matrix& fillMatrix(int m, int n)
{
    Matrix A(m,n);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            float val;
            cin >> val;
            A.insertVal(val, i, j);
            cout << val << " ";
        }
        cout << endl;
    }
    
    return A;
}