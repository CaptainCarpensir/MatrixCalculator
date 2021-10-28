#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "Fraction.h"
using namespace std;

class Matrix
{
    private:
        //Vars
        Fraction** matrix;
    public:
        //Matrix Width and Height
        int m; //Rows
        int n; //Cols

        //Default Constructor
        Matrix();

        //Constructor
        Matrix(int rows, int cols);

        //Copy Constructor
        Matrix(Matrix& A);

        //Destructor
        ~Matrix();

        //Assignment operator overload
        void operator=(const Matrix& A);

        //Operator overload to print
        friend ostream& operator<<(ostream& os, const Matrix& matrix);
    
        /*
        * MEMBER FUNCTIONS & MATRIX ARITHMETIC
        */
        void insertVal(Fraction val, int row, int col);

        Fraction getVal(int row, int col) const;

        //Arithmetic matrix operations
        Matrix operator+(const Matrix& A) const;

        Matrix operator-(const Matrix& A) const;

        Matrix operator*(const Matrix& A) const;

        Matrix operator*(const Fraction val) const;

        //Matrix operations
        void transpose();

        bool invert();

        void gaussjordan();

        Fraction determinant();

        int rowechelon();

        //void augmentmatrix(Matrix& A);

        void solvematrix(Matrix& b);
    private:
        //Private Functions
        void row_replacement(int row1, int row2, Fraction k);

        void row_interchange(int row1, int row2);

        void row_scaling(int row1, Fraction k);
};

#endif