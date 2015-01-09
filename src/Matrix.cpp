#include <Matrix.h>


Matrix::Matrix(unsigned r, unsigned c) :rows(r), cols(c)
{
	this->Resize(r,c);
}

//copy constructor
/*
Matrix::Matrix(const Matrix& rhs)
{
	this->mat = rhs.mat;
	this->rows = rhs.rows;
	this->cols = rhs.cols;
}
*/

// overload * operator
Matrix Matrix::operator*(const Matrix& rhs)
{
	//check if multplication is possible
	if (cols != rhs.rows) throw "Multiplication error!";

	Matrix res(rows, rhs.cols);

	for (int i = 0; i < rows; ++i) 
	{
		for (int j = 0; j < rhs.cols; ++j) 
		{
			res[i][j] = 0;

			for (int k = 0; k < rhs.rows; ++k) 
			{
				res[i][j] += (*this)[i][k] * rhs[k][j];
			}
		}
	}
	return res;
}

// overload + operator
Matrix Matrix::operator+(const Matrix& rhs)
{
	//check if + is possible
	if ((rows != rhs.rows) && (cols != rhs.cols)) throw "Addition error!";
	
	Matrix res(rows, cols);

	for(int i=0; i<rows;i++)
	{
		for(int j=0; j<cols;j++)
			res[i][j] = (*this)[i][j] + rhs[i][j];
	}

	return res;

}

// overload - operator
Matrix Matrix::operator-(const Matrix& rhs)
{
	//check if - is possible
	if ((rows != rhs.rows) && (cols != rhs.cols)) throw "Addition error!";
	
	Matrix res(rows, cols);

	for(int i=0; i<rows;i++)
	{
		for(int j=0; j<cols;j++)
			res[i][j] = (*this)[i][j] - rhs[i][j];
	}
	return res;
}