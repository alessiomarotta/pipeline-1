#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <vector>
#include "Vertex.h"

class Matrix {
	public:
		Matrix() : Matrix(4, 4) {}

		Matrix(std::vector<double> m) : Matrix(4, 4, m) {}

		Matrix(size_t rows, size_t cols);

		Matrix(size_t rows, size_t cols, std::vector<double> m);

		double& operator()(size_t row, size_t col);

		Matrix operator*(Matrix n);

		Matrix operator*(double n);

		Vertex operator*(Vertex v);

		Matrix operator+(Matrix n);

		Matrix operator-(Matrix n);
	
	private:
		size_t rows_;
		size_t cols_;

		std::vector<std::vector<double>> m_;
};

#endif
