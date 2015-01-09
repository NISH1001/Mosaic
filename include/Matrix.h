#pragma once

#include <vector>

/*
	A matrix class for matrices of double
	std::vector<std::vector<double>>
*/

class Matrix
{
public:
	Matrix(unsigned rows, unsigned cols);
	Matrix() {}
	//Matrix(const Matrix & rhs); copy constructor
	~Matrix() {}

	/* overload index operator */
	std::vector<double> & operator[](int idx) {	return mat[idx];}
	const std::vector<double> & operator[](int idx) const {	return mat[idx];}

	/*mathematics overload*/
	Matrix operator*(const Matrix & rhs);
	Matrix operator+(const Matrix & rhs);
	Matrix operator-(const Matrix & rhs);

private:
	void Resize(int r, int c) { mat = std::vector<std::vector<double>> (rows, std::vector<double>(cols, 0)); }

public:
	unsigned rows;
	unsigned cols;

private:
	std::vector<std::vector<double>> mat;
};