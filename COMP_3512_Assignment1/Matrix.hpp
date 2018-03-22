#pragma once

#include "Rank.hpp"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <ostream>
using namespace std;

class Matrix
{
	int dimensions;
	double * arr;
	double p{ 0.85 };

public:
	Matrix();
	Matrix(int);
	Matrix(double[], int);
	Matrix(const Matrix&);
	~Matrix();
	void set_value(int, int, double);
	int get_index(int, int) const;
	double get_value(int, int) const;
	void clear();
	Matrix identity();
	friend ostream& operator<<(ostream&, const Matrix&);
	friend bool operator==(const Matrix&, const Matrix&);
	friend bool operator!=(const Matrix&, const Matrix&);
	friend bool operator<(const Matrix&, const Matrix&);
	friend bool operator>(const Matrix&, const Matrix&);
	friend bool operator<=(const Matrix&, const Matrix&);
	friend bool operator>=(const Matrix&, const Matrix&);
	Matrix& operator++();
	Matrix operator++(int);
	Matrix& operator--();
	Matrix operator--(int);
	friend Matrix operator+(Matrix, const Matrix&);
	friend Matrix operator-(Matrix, const Matrix&);
	friend Matrix operator*(Matrix, const Matrix&);
	void swap(Matrix&, Matrix&);
	Matrix& operator=(Matrix);
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	double get_in_degree(int);
	double get_out_degree(int);
	Matrix check_col_for_zeros(Matrix);
	Matrix importance_Matrix();
	Matrix qMatrix();
	Matrix mMatrix(Matrix);
	Rank markProcess(const Matrix&, Rank&);
	Rank finalStep(Rank);
};

