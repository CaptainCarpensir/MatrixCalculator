#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

class Matrix
{
    private:
        //Vars
        float** matrix;
    public:
        //Matrix Width and Height
        int m; //Rows
        int n; //Cols

        //Constructor
        Matrix(int rows, int cols);

        //Destructor
        ~Matrix();

        //Assignment operator overload
        void operator=(Matrix& A);

        //Operator overload to print
        friend ostream& operator<<(ostream& os, const Matrix& matrix);
    
        /*
        * MEMBER FUNCTIONS & MATRIX ARITHMETIC
        */
        void insertVal(float val, int row, int col);

        float getVal(int row, int col) const;

        //Returns matrix, adds calling matrix and parameter matrix (A = B + C)
        Matrix& operator+(const Matrix& A);
};

#endif