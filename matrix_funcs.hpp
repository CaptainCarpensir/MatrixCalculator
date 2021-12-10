using namespace std;

/*
* CONSTRUCTOR & DESTRUCTOR
*/

//Default Constructor
template <typename T>
Matrix<T>::Matrix()
{
	m = 1;
	n = 1;
	matrix = new T*[1];
	matrix[0] = new T[1];
	matrix[0][0] = 0;
};

//Constructor
template <typename T>
Matrix<T>::Matrix(const int rows, const int cols)
{
	//Setting variables
	matrix = new T*[rows];
	m = rows;
	n = cols;

	//Creating 2D array
	for(int i = 0; i < rows; i++)
	{
		matrix[i] = new T[cols];
		for(int j = 0; j < cols; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

//Copy Constructor
template <typename T>
Matrix<T>::Matrix(const Matrix& A)
{
	m = A.m;
	n = A.n;
	matrix = new T*[m];

	for(int i = 0; i < m; i++)
	{
		matrix[i] = new T[n];
		for(int j = 0; j < n; j++)
		{
			matrix[i][j] = A.matrix[i][j];
		}
	}
}

//Destructor
template <typename T>
Matrix<T>::~Matrix()
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
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& A)
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
	matrix = new T*[m];

	//Creating 2D array
	for(int i = 0; i < m; i++)
	{
		matrix[i] = new T[n];
		for(int j = 0; j < n; j++)
		{
			matrix[i][j] = A.matrix[i][j];
		}
	}

	return *this;
}

//Operator overload to print
template <typename T>
ostream& operator<<(ostream& os, const Matrix<T>& matrix)
{
	for(int i = 0; i < matrix.m; i++)
	{
		for(int j = 0; j < matrix.n; j++)
		{
			os << matrix.matrix[i][j] << " ";
		}
		if(i < matrix.m - 1) os << endl;
	}

	return os;
}

/*
* MEMBER FUNCTIONS
*/

//Inserts a value at a specific places
template <typename T>
void Matrix<T>::insertVal(T& val, int row, int col)
{
	matrix[row][col] = val;
}

template <typename T>
T& Matrix<T>::getVal(int row, int col) const
{
	return this->matrix[row][col];
}

//Returns matrix, adds calling matrix and parameter matrix (A = B + C)
template <typename T>
Matrix<T>& Matrix<T>::operator+(const Matrix& A)
{
	//If the matrices have different sizes, it returns the left hand matrix (in this case, B)
	if(m != A.m || n != A.n) return *this;

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			//Adds values together, inserts in same place
			matrix[i][j] += A.matrix[i][j];
		}
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*(const Matrix& A)
{
	if(n != A.m) return *this;

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < A.n; j++)
		{
			//Insert value of the dot product of the vectors at row(i) of this matrix, and col(j) of A
			T sum; 
			for(int k = 0; k < n; k++)
			{
				sum += (matrix[i][k] * A.matrix[k][j]);
			}
			matrix[i][j] = sum;
		}
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*(const T& val)
{
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			matrix[i][j] *= val;
		}
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-(const Matrix<T>& A)
{
	if(m != A.m || n != A.n) return *this;

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			matrix[i][j] -= A.matrix[i][j];
		}
	}

	return *this;
}

template <typename T>
void Matrix<T>::transpose()
{
	T** new_matrix = new T*[n];

	//Copy over transpose
	for(int i = 0; i < n; i++)
	{
		new_matrix[i] = new T[m];
		for(int j = 0; j < m; j++)
		{
			new_matrix[i][j] = matrix[j][i];
		}
	}

	//Deleting pointer matrix
	for(int i = 0; i < m; i++) 
	{
		delete[] matrix[i];
	}

	//Pointing to new matrix, set temp pointer to nullptr
	matrix = new_matrix;
	new_matrix = nullptr;
}

template <typename T>
bool Matrix<T>::invert()
{
	//Return false if there is no 
	if(m != n) return false;

	//Create temp matrix
	Matrix<T> temp(m,n);
	temp = *this;

	//Create identity matrix
	Matrix<T> identity(m,n);
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

template <typename T>
void Matrix<T>::gaussjordan()
{
	rowechelon();
	//Continue to remove areas above pivots

	T f(1);

	//Loop bottom left to top right, reading one line at a time, 
	// the pivot is the first non-zero digit found on each line
	for(int i = m-1; i >= 0; i--)
	{
		for(int j = 0; j < n; j++)
		{
			//Pivot found, reduce all points above the pivot to 0, then divide the pivot to 1 by row scaling
			if(matrix[i][j] != 0)
			{
				row_scaling(i, (f/matrix[i][j]));
				for(int k = 0; k < i; k++)
				{
					row_replacement(k, i, ((-matrix[k][j])/matrix[i][j]));
				}
				j = n;
			}
		}
	}
}

template <typename T>
T Matrix<T>::determinant()
{
	T default_frac;
	if(m != n) return default_frac;

	Matrix<T> temp;
	temp = *this;
	int swaps = temp.rowechelon();

	//Sets the determinant to start off as -1 or +1 based on how many row swaps occured
	T determinant((swaps%2==1)?(-1):(1), 1);

	for(int i = 0; i < m; i++)
	{
		determinant *= temp.matrix[i][i];
	}

	return determinant;
}

//RETURNS NUMBER OF ROW SWAPS USED IN ORDER TO CALCULATE DETERMINANT
template <typename T>
int Matrix<T>::rowechelon()
{
	/*
	*   To reduce to Row Echelon form:
	*
	*   1. Loop through rows
	*   2. On each row, first: check if the position below previous pivot is 0, swap with first position that is not.
	*	   If there is no zero on the column below the previous pivot height, skip this row
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
				row_replacement(j, curr_pivot_height, ((-matrix[j][i])/matrix[curr_pivot_height][i]));
			}
		}
   }

   return swaps;
}

//Requires the calling matrix, and the parameter matrix to have the same number of rows
template <typename T>
void Matrix<T>::augmentmatrix(const Matrix<T>& A)
{
	if(m != A.m) return;

	//Creating temp matrix
	Matrix<T> temp(*this);

	//Deleting current matrix
	for(int i = 0; i < m; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

	//Remaking matrix
	n = A.n + temp.n;
	matrix = new T*[m];

	for(int i = 0; i < m; i++)
	{
		matrix[i] = new T[n];
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
template <typename T>
void Matrix<T>::columnspace() const
{
	//Create temp and get REF
	Matrix<T> temp(*this);
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
template <typename T>
void Matrix<T>::nullspace() const
{
	//Make temp and get REF
	Matrix<T> temp(*this);
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
	T **basis = new T*[free_vars];

	//Now loop through all columns and store information to print basis vectors
	free_vars = 0;
	for(int i = 0; i < n; i++)
	{
		//Check if column has free variable
		if(!pivots[i])
		{
			basis[free_vars] = new T[n];
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

template <typename T>
void Matrix<T>::solvematrix(const Matrix<T>& b) const
{
	//Create augmented matrix and reduce to REF
	Matrix<T> temp(*this);
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

template <typename T>
T Matrix<T>::dotproduct(const Matrix& b)
{
	T answer;

	if(!(n == b.m && m == 1 && b.n == 1)) return answer;

	for(int i = 0; i < n; i++)
	{
		answer += (matrix[0][i] * b.matrix[i][0]);
	}

	return answer;
}

template <typename T>
Matrix<T>& Matrix<T>::project(const Matrix<T>& p)
{
	if(n != 1) return *this;

	//Creating a list of n vectors to be added
	Matrix<T> *list[p.n];

	//Initializing
	for(int i = 0; i < p.n; i++)
	{
		list[i] = new Matrix<T>(p.m, 1);
	}

	for(int i = 0; i < p.n; i++)
	{
		//Get vector for current column
		Matrix<T> currCol(1, p.m);
		for(int j = 0; j < p.m; j++)
		{
			currCol.matrix[0][j] = p.matrix[j][i];
		}

		Matrix<T> colTranspose(currCol);
		colTranspose.transpose();
		T multiplier = currCol.dotproduct(*this)/currCol.dotproduct(colTranspose);
		for(int j = 0; j < p.m; j++)
		{
			list[i]->matrix[j][0] = multiplier * currCol.matrix[0][j];
		}
	}

	for(int i = 0; i < p.n; i++)
	{
		*this = (*this + *list[i]);
	}

	for(int i = 0; i < p.n; i++)
	{
		delete list[i];
	}

	return *this;
}

template <typename T>
void Matrix<T>::gramschmidt()
{

}

template <typename T>
void Matrix<T>::eigenvectors()
{

}

/*
* PRIVATE MEMBER FUNCTIONS
*/

//Replace row1 with the sum of row1 + row2 * k
template <typename T>
void Matrix<T>::row_replacement(const int row1, const int row2, const T& k)
{
	for(int i = 0; i < n; i++) matrix[row1][i] = matrix[row1][i] + (k * matrix[row2][i]);
}

//Swap row1 and row2
template <typename T>
void Matrix<T>::row_interchange(const int row1, const int row2)
{
	T *temp = new T[n];
	for(int i = 0; i < n; i++)
	{
		temp[i] = matrix[row1][i];
		matrix[row1][i] = matrix[row2][i];
		matrix[row2][i] = temp[i];
	}
	delete[] temp;
}

//Scale row1 by constant k
template <typename T>
void Matrix<T>::row_scaling(const int row1, const T& k)
{
	for(int i = 0; i < n; i++)
	{
		matrix[row1][i] *= k;
	}
}