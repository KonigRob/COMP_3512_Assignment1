#include "Matrix.hpp"
// COMP_3512_Lab3.cpp : Defines the entry point for the console application.
//

/*
DESCP:  Main constructor for the Matrix class
PRE: Takes no parameters
POST: Created a default 1x1 matrix with 0 stored in it.
*/
Matrix::Matrix() : dimensions{ 1 }, arr(new double[1])
{
	arr[0] = { 0.0 };
}

/*
DESCP: Constructor that takes an int for the Matrix class
PRE: Takes an int for the parament, and assumes this int is an non-negative number
POST: Creates a Matrix of size n^2 stored with 0 in it.
RETURN:
*/
Matrix::Matrix(int size) : dimensions{ size }, arr{ new double[size*size] }
{
	clear();
}

/*
DESCP: Constructor that takes an int array and an int for the Matrix class
PRE: Assumes that the array is not null, and the size of the array is not a negative number
POST: Cop
RETURN:
*/
Matrix::Matrix(double newArray[], int size_of_array) : dimensions{ (int)sqrt(size_of_array) }
{
	if (pow(dimensions, 2) != size_of_array) {
		cerr << "Error, wrong size" << endl;
	}
	arr = new double[size_of_array];
	for (int i = 0; i < size_of_array; ++i) {
		arr[i] = newArray[i];
	}
}

/*
DESCP:
PRE:
POST:
RETURN:
*/
Matrix::Matrix(const Matrix & other) : dimensions{ other.dimensions }
{
	arr = new double[dimensions * dimensions];
	for (int i = 0; i < dimensions * dimensions; ++i) {
		arr[i] = other.arr[i];
	}
}

Matrix::~Matrix()
{
	delete[] arr;
}

void Matrix::set_value(int row, int col, double new_value)
{
	arr[row * dimensions + col] = new_value;
}

int Matrix::get_index(int row, int col) const
{
	return row * dimensions + col;
}

double Matrix::get_value(int row, int col) const
{
	return arr[get_index(row, col)];
}

void Matrix::clear()
{
	for (int index = 0; index < dimensions * dimensions; ++index) {
		arr[index] = 0.0;
	}
}

Matrix Matrix::identity()
{
	Matrix a(dimensions);
	for (int row = 0; row < dimensions; ++row) {
		for (int col = 0; col < dimensions; ++col) {
			if (row == col) {
				a.set_value(row, col, 1);
			}
			else {
				a.set_value(row, col, 0);
			}
		}
	}
	return a;
}

ostream& operator<<(ostream & output, const Matrix & matrix)
{
	for (int row = 0; row < matrix.dimensions; ++row) {
		for (int col = 0; col < matrix.dimensions; ++col) {
			output << fixed << setw(10) << left << setprecision(6) << matrix.arr[row * matrix.dimensions + col];
		}
		output << "\n";
	}
	return output;
}

bool operator==(const Matrix & lefthand, const Matrix & righthand)
{
	if (lefthand.dimensions != righthand.dimensions) {
		return false;
	}
	for (int row = 0; row < lefthand.dimensions; ++row) {
		for (int col = 0; col < righthand.dimensions; ++col) {
			if (lefthand.get_index(row, col) != righthand.get_index(row, col)) {
				return false;
			}
		}
	}
	return true;
}

bool operator!=(const Matrix & lefthand, const Matrix & righthand)
{
	return !operator==(lefthand, righthand);
}

bool operator<(const Matrix & lefthand, const Matrix & righthand)
{
	return lefthand.dimensions < righthand.dimensions;
}

bool operator>(const Matrix & lefthand, const Matrix & righthand)
{
	return operator< (righthand, lefthand);
}

bool operator<=(const Matrix & lefthand, const Matrix & righthand)
{
	return !operator> (lefthand, righthand);
}

bool operator>=(const Matrix & lefthand, const Matrix & righthand)
{
	return !operator< (lefthand, righthand);
}

Matrix operator+(Matrix lefthand, const Matrix & righthand)
{
	lefthand += righthand;
	return lefthand;
}

Matrix operator-(Matrix lefthand, const Matrix & righthand)
{
	lefthand -= righthand;
	return lefthand;
}

Matrix operator*(Matrix lefthand, const Matrix & righthand)
{
	lefthand *= righthand;
	return lefthand;
}

Matrix& Matrix::operator++()
{
	for (int row = 0; row < dimensions; ++row) {
		for (int col = 0; col < dimensions; ++col) {
			int tmp = row * dimensions + col;
			arr[tmp] = 1 + arr[tmp];
		}
	}
	return *this;
}

Matrix Matrix::operator++(int)
{
	Matrix tmp(*this);
	operator++();
	return tmp;
}

Matrix& Matrix::operator--()
{
	for (int row = 0; row < dimensions; ++row) {
		for (int col = 0; col < dimensions; ++col) {
			int tmp = row * dimensions + col;
			arr[tmp] = arr[tmp] - 1;
		}
	}
	return *this;
}

Matrix Matrix::operator--(int)
{
	Matrix tmp(*this);
	operator--();
	return tmp;
}

void Matrix::swap(Matrix & lefthand, Matrix & righthand)
{
	using std::swap;
	swap(lefthand.dimensions, righthand.dimensions);
	swap(lefthand.arr, righthand.arr);
}

Matrix& Matrix::operator=(Matrix righthand)
{
	swap(*this, righthand);
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& righthand)
{
	for (int row = 0; row < dimensions; ++row) {
		for (int col = 0; col < dimensions; ++col) {
			int tmp = row * dimensions + col;
			arr[row * dimensions + col] += righthand.arr[row * dimensions + col];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& righthand)
{
	for (int row = 0; row < dimensions; ++row) {
		for (int col = 0; col < dimensions; ++col) {
			int tmp = row * dimensions + col;
			arr[tmp] -= righthand.arr[tmp];
		}
	}
	return *this;
}

Matrix & Matrix::operator*=(const Matrix& righthand)
{	
	Matrix tmp(dimensions);
	for (int row = 0; row < dimensions; ++row) {
		for (int col = 0; col < dimensions; ++col) {
			for (int k = 0; k < dimensions; ++k) {
				tmp.arr[row * dimensions + col] += arr[row * dimensions + k] * righthand.arr[k * dimensions + col];
			}
		}
	}
	for (int row = 0; row < dimensions; ++row) {
		for (int col = 0; col < dimensions; ++col) {
			arr[row * dimensions + col] = tmp.arr[row * dimensions + col];
		}
	}
	return *this;
}

double Matrix::get_in_degree(int r)
{	
	double sum = 0.0;
	for (int i = r * dimensions; i < (r + 1) * dimensions; ++i) {
		if (arr[i] == 1) {
			++sum;
		}
	}
	return sum;
}

double Matrix::get_out_degree(int c)
{
	double sum = 0.0;
	for (int i = c; i < dimensions * dimensions; i += dimensions) {
		if (arr[i] == 1) {
			++sum;
		}
	}
	return sum;
}

/*So, hi sleepy Robbob
Basically your program loops from left to right, moving downwards.  So it scans the rows one by one.
This code below should scan them column one by one.  BUT
right now it isn't able to see more than 1 column if found. 
You could loop through, and return -1 if it isn't found.  If it is found, then return the column that you need to loop through to set to the proper thing.
Then on your next check, run it again, but this time calling the updated input.*/
Matrix Matrix::check_col_for_zeros(Matrix a)
{	
	for (int col = 0; col < dimensions; ++col) {
		bool f = false;
		for (int row = 0; row < dimensions; ++row) {
			if (arr[get_index(row, col)] == 1) {
				f = true;
			}
		}
		if (f == false) {
			for (int row = 0; row < dimensions; ++row) {
				a.set_value(row, col, 1.0 / dimensions);
			}
		}
	}
	return a;
}

Matrix Matrix::importance_Matrix()
{
	Matrix a(dimensions);
	a = check_col_for_zeros(a);
	for (int row = 0; row < dimensions; ++row) {
		for (int col = 0; col < dimensions; ++col) {
				if (arr[get_index(row, col)] == 1) {
					a.set_value(row, col, 1.0 / get_out_degree(col));
				}
		}
	}
	return a;
}

Matrix Matrix::qMatrix()
{
	Matrix a(dimensions);
	for (int row = 0; row < dimensions; ++row) {
		for (int col = 0; col < dimensions; ++col) {
				a.set_value(row, col, 1.0 / dimensions);
		}
	}
	return a;
}

Matrix Matrix::mMatrix(Matrix q)
{
	Matrix a(dimensions);
	for (int row = 0; row < dimensions; ++row) {
		for (int col = 0; col < dimensions; ++col) {
			a.set_value(row, col, (0.85 * arr[get_index(row, col)]) + (0.15 * q.arr[get_index(row, col)]));
		}
	}
	return a;
}

Rank Matrix::markProcess(const Matrix &m, Rank &rank)
{
	Rank data(dimensions);
	double sum{ 0 };
	int z = 0, x = 0;
	//cout << "Rank m: " << m << endl << endl;
	//cout << "Rank m: " << m << endl << endl;
	do {
		z++;
		for (int index = 0; index < dimensions; ++index) {
			rank.arr[index] = data.arr[index];
		}
		//takes the data, and stores the stuff in it
		for (int row = 0; row < dimensions; ++row) {
			sum = 0.0;
			for (int col = 0; col < dimensions; ++col) {
				sum += (m.arr[row * dimensions + col] * rank.arr[col]);
				//cout << sum << " : " << z++ << endl;
			}
			data.arr[row] = sum;
			/*
			cout << "Data value at index " << i << " : " << data.arr[i] << "   loop: " << z << endl;
			cout << "Rank value at index " << i << " : " << rank.arr[i] << "   loop: " << z << endl;*/
			
		}
		//checks if they aren't the same, but when it loops again, it'll overwrite the data I just wrote.
		//while(copyOfData != data)
	} while (data != rank);
	return data;
}

Rank Matrix::finalStep(Rank rank)
{
	double sum = 0.0;
	for (int index = 0; index < dimensions; ++index) {
		sum += rank.arr[index];
	}
	for (int index = 0; index < dimensions; ++index) {
		rank.arr[index] /= sum;
	}
	return rank;
}