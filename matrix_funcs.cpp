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
    matrix = new Fraction*[1];
    matrix[0] = new Fraction[1];
    matrix[0][0] = 0;
};

//Constructor
Matrix::Matrix(int rows, int cols)
{
    //Setting variables
    matrix = new Fraction*[rows];
    m = rows;
    n = cols;

    //Creating 2D array
    for(int i = 0; i < rows; i++)
    {
        matrix[i] = new Fraction[cols];
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
    matrix = new Fraction*[m];

    for(int i = 0; i < m; i++)
    {
        matrix[i] = new Fraction[n];
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
    matrix = new Fraction*[m];

    //Creating 2D array
    for(int i = 0; i < m; i++)
    {
        matrix[i] = new Fraction[n];
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
void Matrix::insertVal(Fraction val, int row, int col)
{
    matrix[row][col] = val;
}

void Matrix::insertVal(int val, int row, int col)
{
    Fraction new_val(val, 1);
    matrix[row][col] = new_val;
}

Fraction Matrix::getVal(int row, int col) const
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
            Fraction sum; 
            for(int k = 0; k < n; k++)
            {
                sum += (matrix[i][k] * A.matrix[k][j]);
                answer.matrix[i][j] = sum;
            }
        }
    }

    return answer;
}

Matrix Matrix::operator*(const Fraction val) const
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
    //Return false if there is no 
    if(m != n) return false;

    //Create temp matrix
    Matrix temp(m,n);
    temp = *this;

    //Create identity matrix
    Matrix identity(m,n);
    for(int i = 0; i < m; i++)
    {
        identity.matrix[i][i] = 1;
    }

    //Augment temp matrix with identity matrix, then convert to REF
    temp.augmentmatrix(identity);
    temp.gaussjordan();

    //Check for zero rows in the augmented matrix
    bool inverse_exists = true;
    for(int i = 0; i < m; i++)
    {
        bool zero_row = true;
        for(int j = 0; j < n; j++)
        {
            if(temp.matrix[i][j] != 0)
            {
                zero_row = false;
                j = n;
            }
        }
        if(zero_row)
        {
            inverse_exists = false;
            i = m;
            return false;
        }
    }

    //Code reaches this point, inverse exists, and resides in the second half of the augmented matrix
    //Loop to change into inverse
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[i][j] = temp.matrix[i][j+n];
        }
    }

    return true;
}

void Matrix::gaussjordan()
{
    rowechelon();
    //Continue to remove areas above pivots

    Fraction f(1,1);

    //Loop bottom left to top right, reading one line at a time, 
    // the pivot is the first non-zero digit found on each line
    for(int i = m-1; i >= 0; i--)
    {
        for(int j = 0; j < n; j++)
        {
            //Pivot found, reduce all points above the pivot to 0, then divide the pivot to 1 by row scaling
            if(matrix[i][j] != 0)
            {
                row_scaling(i, f/matrix[i][j]);
                for(int k = 0; k < i; k++)
                {
                    row_replacement(k, i, (-matrix[k][j])/matrix[i][j]);
                }
                j = n;
            }
        }
    }
}

Fraction Matrix::determinant()
{
    Fraction default_frac;
    if(m != n) return default_frac;

    Matrix temp;
    temp = *this;
    int swaps = temp.rowechelon();

    //Sets the determinant to start off as -1 or +1 based on how many row swaps occured
    Fraction determinant((swaps%2==1)?(-1):(1), 1);

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
                row_replacement(j, curr_pivot_height, (-matrix[j][i])/matrix[curr_pivot_height][i]);
            }
        }
   }

   return swaps;
}

//Requires the calling matrix, and the parameter matrix to have the same number of rows
void Matrix::augmentmatrix(const Matrix& A)
{
    if(m != A.m) return;

    //Creating temp matrix
    Matrix temp(*this);

    //Deleting current matrix
    for(int i = 0; i < m; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    //Remaking matrix
    n = A.n + temp.n;
    matrix = new Fraction*[m];

    for(int i = 0; i < m; i++)
    {
        matrix[i] = new Fraction[n];
        for(int j = 0; j < n; j++)
        {
            //Logic which inserts either val from temp matrix or parameter matrix
            if(j < temp.n)
            {
                matrix[i][j] = temp.matrix[i][j];
            }
            else{
                matrix[i][j] = A.matrix[i][j - temp.n];
            }
        }
    }
}

//Finds and prints the basis of the column space
void Matrix::columnspace()
{
    //Create temp and get REF
    Matrix temp(*this);
    temp.gaussjordan();

    //Find pivot column positions
    bool *pivots = new bool[n];
    int curr_pos = 0;
    for(int i = 0; i < temp.n; i++) pivots[i] = false;
    for(int i = 0; i < m; i++)
    {
        for(int j = curr_pos; j < n; j++)
        {
            if(temp.matrix[i][j] != 0)
            {
                pivots[j] = true;
                curr_pos = j + 1;
                j = n;
            }
        }
    }

    //Print basis from independent vectors of A
    int pivot_cnt = 0;
    for(int i = 0; i < n; i++)
    {
        //If column is a pivot column, loop through it and print it as a basis
        if(pivots[i])
        {
            cout << (char)('a' + pivot_cnt) << ": ";
            for(int j = 0; j < m; j++)
            {
                cout << matrix[j][i] << " ";
            }
            cout << endl;
            pivot_cnt++;
        }
    }

    delete[] pivots;
}

//Finds and prints the basis of the solution set for Ax = 0
void Matrix::nullspace()
{
    //Make temp and get REF
    Matrix temp(*this);
    temp.gaussjordan();

    //Find # of pivot columns and their coordinates
    bool *pivots = new bool[n];
    int curr_pos = 0;
    int free_vars = 0;
    for(int i = 0; i < temp.n; i++) pivots[i] = false;
    for(int i = 0; i < m; i++)
    {
        for(int j = curr_pos; j < n; j++)
        {
            if(temp.matrix[i][j] != 0)
            {
                pivots[j] = true;
                curr_pos = j + 1;
                j = n;
            }
            else
            {
                free_vars++;
            }
        }
    }

    //Create 2D array for basis vectors, # of basis vectors = # of free vars
    Fraction **basis = new Fraction*[free_vars];

    //Now loop through all columns and store information to print basis vectors
    free_vars = 0;
    for(int i = 0; i < n; i++)
    {
        //Check if column has free variable
        if(!pivots[i])
        {
            basis[free_vars] = new Fraction[n];
            int pivot_cnt = 0;
            int free_cnt = 0;
            for(int j = 0; j < n; j++)
            {
                if(pivots[j])
                {
                    basis[free_vars][j] = -(temp.matrix[pivot_cnt][i]);
                    pivot_cnt++;
                }
                else
                {
                    basis[free_vars][j] = ((free_cnt == free_vars) ? 1 : 0);
                    free_cnt++;
                }
            }
            free_vars++;
        }
    }

    //Print nullspace
    for(int i = 0; i < free_vars; i++)
    {
        cout << (char)('a' + i) << ": ";
        for(int j = 0; j < n; j++)
        {
            cout << basis[i][j] << " ";
        }
        cout << endl;
        delete[] basis[i];
    }
    delete[] basis;

    //Case that the nullspace is just the zero vector
    if(free_vars == 0)
    {
        cout << "a: 0";
    }

    delete[] pivots;
}

void Matrix::solvematrix(const Matrix& b)
{
    //Create augmented matrix and reduce to REF
    Matrix temp(*this);
    temp.augmentmatrix(b);
    temp.gaussjordan();

    //Make array that contains info on pivot columns
    bool *pivots = new bool[temp.n];
    int curr_pos = 0;
    for(int i = 0; i < temp.n; i++) pivots[i] = false;
    for(int i = 0; i < m; i++)
    {
        for(int j = curr_pos; j < temp.n; j++)
        {
            if(temp.matrix[i][j] != 0)
            {
                pivots[j] = true;
                curr_pos = j + 1;
                j = temp.n;
            }
        }
    }

    //Case where there's a pivot in the last column, no solution
    if(pivots[temp.n - 1]) 
    {
        cout << "No solution." << endl;
        delete[] pivots;
        return;
    }

    //Checking homogeniety
    bool ishomogenous = true;
    for(int i = 0; i < m; i++)
    {
        if(temp.matrix[i][temp.n - 1] != 0) ishomogenous = false;
    }

    if(!ishomogenous)
    {
        //Print particular solution
        cout << "Particular solution: ";
        for(int i = 0; i < m; i++)
        {
            cout << temp.matrix[i][temp.n - 1] << " ";
        }
        cout << "\nPlus the span of: " <<  endl;
    }

    if(ishomogenous) cout << "Span: " << endl;

    nullspace();

    delete[] pivots;
}


void Matrix::eigenvectors()
{

}

/*
* PRIVATE MEMBER FUNCTIONS
*/

//Replace row1 with the sum of row1 + row2 * k
void Matrix::row_replacement(int row1, int row2, Fraction k)
{
    for(int i = 0; i < n; i++) matrix[row1][i] = matrix[row1][i] + (k * matrix[row2][i]);
}

//Swap row1 and row2
void Matrix::row_interchange(int row1, int row2)
{
    Fraction *temp = new Fraction[n];
    for(int i = 0; i < n; i++)
    {
        temp[i] = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp[i];
    }
    delete[] temp;
}

//Scale row1 by constant k
void Matrix::row_scaling(int row1, Fraction k)
{
    for(int i = 0; i < n; i++)
    {
        matrix[row1][i] *= k;
    }
}