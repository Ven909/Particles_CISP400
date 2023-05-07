#include "Matrices.h"

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols) // constructor
	{
		rows = _rows;
		cols = _cols;

		a.resize(rows, vector<double>(cols, 0));
	}

	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(10) << a(i, j) << " ";
			}
			os << endl;
		}
		return os; //allows chaining statements ex: cout << a << endl
	}


	Matrix operator+(const Matrix& a, const Matrix& b) // Adds 2 matrixes together, then returns a matrix
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), a.getCols()); // Creates Matrix c, using the rows and cols sizes of a, that holds the values of the added elemets of matrixes a & b

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}

		return c; // returns the matrix, then C will not exist until we run this operator again
	}

	Matrix operator*(const Matrix& a, const Matrix& b) // Multiplies 2 matrixes togther, then returns a matrix, does not multiply simply like c[1][1] = a[1][1] * b[1][1]
	{
		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), b.getCols());

		for (int k = 0; k < a.getRows(); k++)
		{
			for (int i = 0; i < b.getCols(); i++)
			{
				for (int j = 0; j < b.getRows(); j++)
				{
					c(k, i) += a(k, j) * b(j, i);
				}
			}
		}

		return c;
	}


	bool operator==(const Matrix& a, const Matrix& b)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (abs(a(i, j) - b(i, j)) >= 0.001)
				{
					return false;
				}
			}
		}
		return true;

	}

	bool operator!=(const Matrix& a, const Matrix& b)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (abs(a(i, j) - b(i, j)) >= 0.001)
				{
					return true;
				}
			}
		}
		return false;
	}

	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
	{
		a.at(0).at(0) = cos(theta);
		a.at(0).at(1) = -sin(theta);
		a.at(1).at(0) = sin(theta);
		a.at(1).at(1) = cos(theta);

	}

	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
	{
		a.at(0).at(0) = scale;
		a.at(0).at(1) = 0;
		a.at(1).at(0) = 0;
		a.at(1).at(1) = scale;
	}

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
	{
		for (int i = 0; i < nCols; i++)
		{
			a.at(0).at(i) = xShift;
			a.at(1).at(i) = yShift;
		}
	}
}
