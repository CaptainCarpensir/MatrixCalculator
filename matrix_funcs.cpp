#include "Matrix.h"

using namespace std;

/*
* CONSTRUCTOR & DESTRUCTOR
*/

//Default Constructor
Matrix::Matrix()
{
    m = 1;
    n = 1;
    matrix = new float*[1];
    matrix[1] = new float[1];
};

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

//Copy Constructor
Matrix::Matrix(Matrix& A)
{
    m = A.m;
    n = A.n;
    matrix = new float*[m];

    for(int i = 0; i < m; i++)
    {
        matrix[i] = new float[n];
        for(int j = 0; j < n; j++)
        {
            matrix[i][j] = A.matrix[i][j];
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
void Matrix::operator=(const Matrix& A)
{
    //Destroying
    for(int i = 0; i < m; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    //Setting variables
    m = A.m;
    n = A.n;
    matrix = new float*[m];

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
        if(i < matrix.m - 1) cout << endl;
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
Matrix Matrix::operator+(const Matrix& A) const
{
    Matrix answer(m,n);

    //If the matrices have different sizes, it returns the left hand matrix (in this case, B)
    if(m != A.m || n != A.n) return answer;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            //Adds values together, inserts in same place
            answer.matrix[i][j] = matrix[i][j] + A.matrix[i][j];
        }
    }

    return answer;
}

Matrix Matrix::operator*(const Matrix& A) const
{
    Matrix answer(m, A.n);

    if(n != A.m) return answer;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < A.n; j++)
        {
            //Insert value of the dot product of the vectors at row(i) of this matrix, and col(j) of A
            float sum = 0; 
            for(int k = 0; k < n; k++)
            {
                sum += (matrix[i][k] * A.matrix[k][j]);
                answer.matrix[i][j] = sum;
            }
        }
    }

    return answer;
}

Matrix Matrix::operator*(const float val) const
{
    Matrix answer(m,n);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            answer.matrix[i][j] = matrix[i][j] * val;
        }
    }

    return answer;
}

Matrix Matrix::operator-(const Matrix& A) const
{
    Matrix answer(m,n);

    if(m != A.m || n != A.n) return answer;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            answer.matrix[i][j] = matrix[i][j] - A.matrix[i][j];
        }
    }

    return answer;
}

void Matrix::transpose()
{
    Matrix temp(n,m);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            temp.matrix[j][i] = matrix[i][j];
        }
    }

    *this = temp;
}

bool Matrix::invert()
{
    Matrix temp(m,n);

    *this = temp;

    return false;
}

void Matrix::gaussjordan()
{
    rowechelon();
    //Continue to remove areas above pivots

    //Loop bottom left to top right, reading one line at a time, 
    // the pivot is the first non-zero digit found on each line
    for(int i = m-1; i >= 0; i--)
    {
        for(int j = 0; j < n; j++)
        {
            //Pivot found, reduce all points above the pivot to 0, then divide the pivot to 1 by row scaling
            if(matrix[i][j] != 0)
            {
                for(int k = 0; k < i; k++)
                {
                    row_replacement(k, i, -matrix[k][j]/matrix[i][j]);
                }
                row_scaling(i, 1/matrix[i][j]);
                j = n;
            }
        }
    }
}

float Matrix::determinant()
{
    if(m != n) return 0;

    Matrix temp;
    temp = *this;
    int swaps = temp.rowechelon();

    float determinant = (swaps%2==1)?(-1):(1);

    for(int i = 0; i < m; i++)
    {
        determinant *= temp.matrix[i][i];
    }

    return determinant;
}

//RETURNS NUMBER OF ROW SWAPS USED IN ORDER TO CALCULATE DETERMINANT
int Matrix::rowechelon()
{
    /*
    *   To reduce to Row Echelon form:
    *
    *   1. Loop through rows
    *   2. On each row, first: check if the position below previous pivot is 0, swap with first position that is not.
    *       If there is no zero on the column below the previous pivot height, skip this row
    *   3. If there are numbers below the pivot position, use row replacement to make zeroes below the rows
    * 
    *   Repeat the thre previous steps until the whole matrix has been checked
    */

   int curr_pivot_height = -1;
   int pivot_col;
   int swaps = 0;

   for(int i = 0; i < n; i++)
   {
        //Loop through the column to put a non-zero value at the pivot position. If all zeros, it isn't a pivot column.
        pivot_col = false;
        for(int j = curr_pivot_height + 1; j < m; j++)
        {
            if(matrix[j][i] != 0) 
            {
                if(curr_pivot_height + 1 != j) swaps++;
                row_interchange(curr_pivot_height + 1, j);
                curr_pivot_height++;
                j = m;
                pivot_col = true;
            }
        }

        if(pivot_col)
        {
            //Row replacement to create all zeroes
            for(int j = curr_pivot_height + 1; j < m; j++)
            {
                row_replacement(j, curr_pivot_height, -matrix[j][i]/matrix[curr_pivot_height][i]);
            }
        }
   }

   return swaps;
}

//void Matrix::augmentmatrix(Matrix& A);

void solvematrix(Matrix& b);

/*
* PRIVATE MEMBER FUNCTIONS
*/

//Replace row1 with the sum of row1 + row2 * k
void Matrix::row_replacement(int row1, int row2, float k)
{
    for(int i = 0; i < n; i++) matrix[row1][i] = matrix[row1][i] + (k * matrix[row2][i]);
}

//Swap row1 and row2
void Matrix::row_interchange(int row1, int row2)
{
    float *temp = new float[n];
    for(int i = 0; i < n; i++)
    {
        temp[i] = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp[i];
    }
    delete[] temp;
}

//Scale row1 by constant k
void Matrix::row_scaling(int row1, float k)
{
    for(int i = 0; i < n; i++)
    {
        matrix[row1][i] *= k;
    }
}