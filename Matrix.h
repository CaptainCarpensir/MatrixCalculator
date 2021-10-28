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
        void insertVal(float val, int row, int col);

        float getVal(int row, int col) const;

        //Arithmetic matrix operations
        Matrix operator+(const Matrix& A) const;

        Matrix operator-(const Matrix& A) const;

        Matrix operator*(const Matrix& A) const;

        Matrix operator*(const float val) const;

        //Matrix operations
        void transpose();

        bool invert();

        void gaussjordan();

        float determinant();

        int rowechelon();

        //void augmentmatrix(Matrix& A);

        void solvematrix(Matrix& b);
    private:
        //Private Functions
        void row_replacement(int row1, int row2, float k);

        void row_interchange(int row1, int row2);

        void row_scaling(int row1, float k);
};

#endif