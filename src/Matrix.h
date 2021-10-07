#ifndef MATRIX_X
#define MATRIX_H

#include <valarray>

class Matrix {
	public:
		Matrix(size_t rows, size_t cols, std::valarray<double> m);

		//Matrix operator*(Matrix n);

		//Vertex operator*(Vertex v);

		//Matrix operator+(Matrix n);

		//double operator()(size_t row, size_t col);
	
	private:
		size_t rows_;
		size_t cols_;

		std::valarray<double> m_;
};

#endif
