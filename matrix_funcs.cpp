#include "Matrix.h"

using namespace std;

/*
* CONSTRUCTOR & DESTRUCTOR
*/

//Constructor
Matrix::Matrix(int rows, int cols)
{
    //Setting variables
    matrix = new float*[rows];
    m = rows;
    n = cols;

    //Creating 2D array
    for(int i = 0; i < rows; i++)
    {
        matrix[i] = new float[cols];
        for(int j = 0; j < cols; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

//Destructor
Matrix::~Matrix()
{
    for(int i = 0; i < m; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}


/*
* OPERATOR OVERLOADS
*/

//Assignment operator overload
void Matrix::operator=(Matrix& A)
{
    //Destroying
    for(int i = 0; i < m; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    //Setting variables
    cout << "what" << endl;
    m = A.m;
    n = A.n;
    cout << "help" << endl;
    matrix = new float*[m];

    cout << "help" << endl;

    //Creating 2D array
    for(int i = 0; i < m; i++)
    {
        matrix[i] = new float[n];
        for(int j = 0; j < n; j++)
        {
            matrix[i][j] = A.matrix[i][j];
        }
    }
}

//Operator overload to print
ostream& operator<<(ostream& os, const Matrix& matrix)
{
    for(int i = 0; i < matrix.m; i++)
    {
        for(int j = 0; j < matrix.n; j++)
        {
            cout << matrix.matrix[i][j] << " ";
        }
        cout << endl;
    }

    return os;
}

/*
* MEMBER FUNCTIONS
*/

//Inserts a value at a specific places
void Matrix::insertVal(float val, int row, int col)
{
    //Potential error handling
    if(!(row >= 0 && row <= m && col >= 0 && col <= n))
    {
        cout << "ERROR: Tried to insert value in an invalid position" << endl;
        return;
    }

    matrix[row][col] = val;
}

float Matrix::getVal(int row, int col) const
{
    return this->matrix[row][col];
}

//Returns matrix, adds calling matrix and parameter matrix (A = B + C)
Matrix& Matrix::operator+(const Matrix& A)
{
    //If the matrices have different sizes, it returns the left hand matrix (in this case, B)
    if(m != A.m || n != A.n) return *this;

    Matrix answer(m,n);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            //Adds values together, inserts in same place
            answer.insertVal(this->getVal(i,j) + A.getVal(i,j),i,j);
        }
    }

    return answer;
}
