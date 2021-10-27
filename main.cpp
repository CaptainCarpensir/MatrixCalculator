#include <iostream>
#include <string>
#include "Matrix.h"

using namespace std;

/*
* Prototypes
*/
void fillMatrix(Matrix& A, int m, int n);

/*
* Main function
*/

int main()
{
    //Variables
    Matrix running_matrix(1,1);
    string input;
    bool input_assist = false;
    bool prev_cleared = true;
    bool finished = false;

    const int NUM_CMDS = 16;
    const string cmds[NUM_CMDS] = 
    {
        "help", "quit", "toggleinput", "clear", "credit", "empty",
        "add", "subtract", "multiply", "invert", "transpose",
        "determinant", "echelon", "gaussjordan", "columnspace", "nullspace"
    };

    enum Command
    {
        //QoL Commands
        help, quit, toggleinput, clear, credit, empty,

        //Matrix Arithmetic
        add, subtract, multiply, invert, transpose,

        //Matrix Operations
        determinant, echelon, gaussjordan, columnspace, nullspace
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
                break;
            case subtract:
                break;
            case multiply:
                break;
            case invert:
                break;
            case transpose:
                break;
            /*
            *   Matrix Operations
            */
            case determinant:
                break;
            case echelon:
                break;
            case gaussjordan:
                break;
            case columnspace:
                break;
            case nullspace:
                break;
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
                cout << "Input assist: " << (input_assist?"On":"Off") << endl;
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
