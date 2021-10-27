#include <iostream>
#include "Matrix.h"

using namespace std;

void fillMatrix(Matrix& A, int m, int n);

int main()
{
    //Variables
    bool finished = false;
    Matrix running_matrix(1,1);
    bool input_assist = false;

    enum Command
    {
        help, quit, toggleinput, multiply, add, subtract, invert, echelon, gaussjordan, determinant
    };

    //Calculator Loop
    while(!finished)
    {
        Command input = help;
        switch (input)
        {
            //QoL Commands
            case help:
                break;
            case quit:
                finished = true;
                break;
            case toggleinput:
                input_assist = !input_assist;
                break;
            //Matrix Operation Commands
        }
    }
}

//Fills a matrix of size M x N based off of standard input stream
void fillMatrix(Matrix& A, int m, int n, bool input_assist)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(input_assist)
            {
                cout << "Enter val in pos (" << i + 1 << ", " << j + 1 << "): ";
            }
            float val;
            cin >> val;
            A.insertVal(val, i, j);
        }
    }
}