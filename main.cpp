#include <iostream>
#include <string>
#include "Matrix.h"

using namespace std;

/*
* Prototypes
*/
Matrix fillMatrix(int m, int n, bool input_assist);

int getRows();

int getCols();

/*
* Main function
*/

static bool input_assist = true;

int main()
{
    //Variables
    Matrix running_matrix(1,1);
    string input;
    bool prev_cleared = true;
    bool finished = false;

    const int NUM_CMDS = 16;
    const string cmds[NUM_CMDS] = 
    {
        "help", "quit", "toggleinput", "clear", "credit", "empty",
        "add", "subtract", "multiply", "transpose",
        "invert", "determinant", "echelon", "gaussjordan", "columnspace", "nullspace"
    };

    enum Command
    {
        //QoL Commands
        help, quit, toggleinput, clear, credit, empty,

        //Matrix Arithmetic
        add, subtract, multiply, transpose,

        //Matrix Operations
        invert, determinant, echelon, gaussjordan, columnspace, nullspace
    };

    //Entering the program
    cout << "--- Matrix Calculator ---" << endl;

    //Calculator Loop
    while(!finished)
    {
        //Getting user input
        cout << "\nEnter a command: ";
        cin >> input;
        cout << endl;

        //Setting command based off user input
        int cmd = empty;
        for (int i = 0; i < NUM_CMDS; i++)
		{
			if (input == cmds[i])
			{
				cmd = i;
				i = NUM_CMDS;
			}
			else
			{
				cmd = empty;
			}
		}

        switch (cmd)
        {
            /*
            *   Matrix Arithmetic
            */
            case add:
            {
                if(prev_cleared) 
                {
                    cout << "Enter matrix 1:" << endl;
                    int m = getRows();
                    int n = getCols();
                    running_matrix = fillMatrix(m, n, input_assist);
                }
                else{
                    cout << "Matrix 1:\n" << running_matrix << endl;
                }
                Matrix A = running_matrix;
                Matrix B;
                cout << "Enter matrix 2:" << endl;
                B = fillMatrix(A.m, A.n, input_assist);
                prev_cleared = false;
                running_matrix = (A + B);
                cout << running_matrix << endl;
                break;
            }
            case subtract:
            {
                if(prev_cleared) 
                {
                    cout << "Enter matrix 1:" << endl;
                    int m = getRows();
                    int n = getCols();
                    running_matrix = fillMatrix(m, n, input_assist);
                }
                else{
                    cout << "Matrix 1:\n" << running_matrix << endl;
                }
                Matrix A = running_matrix;
                Matrix B;
                cout << "Enter matrix 2:" << endl;
                B = fillMatrix(A.m, A.n, input_assist);
                prev_cleared = false;
                running_matrix = (A - B);
                cout << running_matrix << endl;
                break;
            }
            case multiply:
            {
                if(prev_cleared) 
                {
                    cout << "Enter matrix 1:" << endl;
                    int m = getRows();
                    int n = getCols();
                    running_matrix = fillMatrix(m, n, input_assist);
                }
                else{
                    cout << "Matrix 1:\n" << running_matrix << endl;
                }
                Matrix A = running_matrix;
                Matrix B;
                cout << "Enter matrix 2:" << endl;
                int n = getCols();
                B = fillMatrix(A.n, n, input_assist);
                prev_cleared = false;
                running_matrix = (A * B);
                cout << running_matrix << endl;
                break;
            }
            case transpose:
            {
                if(prev_cleared) 
                {
                    cout << "Enter matrix:" << endl;
                    int m = getRows();
                    int n = getCols();
                    running_matrix = fillMatrix(m, n, input_assist);
                }
                prev_cleared = false;
                running_matrix.transpose();
                cout << running_matrix << endl;
                break;
            }
            /*
            *   Matrix Operations
            */
            case invert:
            {
                if(prev_cleared) 
                {
                    cout << "Enter matrix:" << endl;
                    int m = getRows();
                    int n = getCols();
                    running_matrix = fillMatrix(m, n, input_assist);
                }
                prev_cleared = false;
                bool was_invertible;
                was_invertible = running_matrix.invert();
                cout << running_matrix << endl;
                break;
            }
            case determinant:
            {
                if(prev_cleared) 
                {
                    cout << "Enter matrix:" << endl;
                    int m = getRows();
                    int n = getCols();
                    running_matrix = fillMatrix(m, n, input_assist);
                }
                prev_cleared = false;
                Fraction num = running_matrix.determinant();
                cout << num << endl;
                break;
            }
            case echelon:
            {
                if(prev_cleared) 
                {
                    cout << "Enter matrix:" << endl;
                    int m = getRows();
                    int n = getCols();
                    running_matrix = fillMatrix(m, n, input_assist);
                }
                prev_cleared = false;
                running_matrix.rowechelon();
                cout << running_matrix << endl;
                break;
            }
            case gaussjordan:
            {
                if(prev_cleared) 
                {
                    cout << "Enter matrix:" << endl;
                    int m = getRows();
                    int n = getCols();
                    running_matrix = fillMatrix(m, n, input_assist);
                }
                prev_cleared = false;
                running_matrix.gaussjordan();
                cout << running_matrix << endl;
                break;
            }
            case columnspace:
            {
                break;
            }
            case nullspace:
            {
                break;
            }
            /*
            *   QoL Commands
            */
            case help:
                cout << "List of commands:" << endl;
                for(int i = 0; i < NUM_CMDS; i++)
                {
                    cout << "\t- " << cmds[i] << endl;
                }
                break;
            case quit:
                finished = true;
                break;
            case toggleinput:
                cout << "Input assist: " << (input_assist?"Off":"On") << endl;
                input_assist = !input_assist;
                break;
            case clear:
                cout << "Previous matrix cleared." << endl;
                prev_cleared = true;
                break;
            case credit:
                cout << "This calculator was made by Aiden Carpenter." << endl;
                cout << "My public GitHub account is CaptainCarpensir if you'd like to see any of my other projects." << endl;
                cout << "\tThank you for using this!" << endl;
                break;
            case empty:
                cout << "Invalid command. Use \"help\" to see a list of commands." << endl;
                break;
            default:
                cout << "Invalid command. Use \"help\" to see a list of commands." << endl;
                break;
        }
    }

    //Exit program
    cout << "--- Thank you for using this calculator! ---" << endl;
}

/*
* Helper functions
*/

//Fills a matrix of size M x N based off of standard input stream
Matrix fillMatrix(int m, int n, bool input_assist)
{
    Matrix A(m,n);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(input_assist)
            {
                cout << "\tEnter val in pos (" << i + 1 << ", " << j + 1 << "): ";
            }
            string val;
            string num;
            string den;
            cin >> val;

            int n = val.find('/');

            if(n != -1)
            {
                num = val.substr(0,n);
                den = val.substr(n+1);
            }
            else{
                num = val;
                den = "1";
            }

            Fraction matrixVal(stoi(num), stoi(den));

            A.insertVal(matrixVal, i, j);
        }
    }

    return A;
}

int getRows()
{
    int rows;
    if(input_assist) cout << "\tEnter num rows: ";
    cin >> rows;
    return rows;
}

int getCols()
{
    int cols;
    if(input_assist) cout << "\tEnter num cols: ";
    cin >> cols;
    return cols;
}