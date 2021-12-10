#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

template <typename T>
class Matrix;

template <typename T>
ostream& operator<<(ostream&, const Matrix<T>&);

template <typename T>
class Matrix
{
    private:
        //Vars
        T** matrix;
    public:
        //Matrix Width and Height
        int m; //Rows
        int n; //Cols

        //Default Constructor
        Matrix();

        //Constructor
        Matrix(const int rows, const int cols);

        //Copy Constructor
        Matrix(const Matrix<T>& A);

        //Destructor
        ~Matrix();

        //Assignment operator overload
        Matrix<T>& operator=(const Matrix<T>& A);

        //Operator overload to print
        friend ostream& operator<< <T> (ostream& os, const Matrix<T>& matrix);
    
        /*
        * MEMBER FUNCTIONS & MATRIX ARITHMETIC
        */
        void insertVal(T& val, int row, int col);

        T& getVal(int row, int col) const;

        //Arithmetic matrix operations
        Matrix<T>& operator+(const Matrix<T>& A);

        Matrix<T>& operator-(const Matrix<T>& A);

        Matrix<T>& operator*(const Matrix<T>& A);

        Matrix<T>& operator*(const T& val);

        //Matrix operations
        void transpose();

        bool invert();

        void gaussjordan();

        T determinant();

        int rowechelon();

        void augmentmatrix(const Matrix<T>& A);

        void eigenvectors();

        T dotproduct(const Matrix<T>& b);

        //The columns of matrix p must be orthorogonal for this to work ATM
        Matrix<T>& project(const Matrix<T>& p);

		void gramschmidt();

		/*
		*	Prints results, doesn't affect calling object
		*/
		void columnspace() const;

        void nullspace() const;

		void solvematrix(const Matrix<T>& b) const;

    private:
        //Private Functions
        void row_replacement(const int row1, const int row2, const T& k);

        void row_interchange(const int row1, const int row2);

        void row_scaling(const int row1, const T& k);
};

#include "matrix_funcs.hpp"

#endif