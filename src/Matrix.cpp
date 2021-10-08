#include <cstddef>
#include <vector>
#include "Matrix.h"

Matrix::Matrix(size_t rows, size_t cols) {
	rows_ = rows;
	cols_ = cols;

	m_.resize(rows, std::vector<double>(cols, 0.0));
}

Matrix::Matrix(size_t rows, size_t cols, std::vector<double> m) {
	rows_ = rows;
	cols_ = cols;

	m_.resize(rows, std::vector<double>(cols, 0.0));

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			m_[i][j] = m[(i * cols) + j];
		}
	}
}

// TODO: add boundary check
double& Matrix::operator()(size_t row, size_t col) {
   return m_[row][col];
}
