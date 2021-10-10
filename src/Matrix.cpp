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

Matrix Matrix::operator*(Matrix n) {
	Matrix res = Matrix(rows_, cols_);

	for (size_t i = 0; i < rows_; i++) {
		for (size_t j = 0; j < cols_; j++) {
			for (size_t k = 0; k < cols_; k++) {
				res(i, j) += m_[i][k] * n(k, j);
			}
		}
	}

	return res;
}

Matrix Matrix::operator*(double n) {
	Matrix res = Matrix(rows_, cols_);

	for (size_t i = 0; i < rows_; i++) {
		for (size_t j = 0; j < cols_; j++) {
			res(i, j) = n * m_[i][j];
		}
	}

	return res;
}


Matrix Matrix::operator+(Matrix n) {
	Matrix res = Matrix(rows_, cols_);

	for (size_t i = 0; i < rows_; i++) {
		for (size_t j = 0; j < cols_; j++) {
			res(i, j) = m_[i][j] + n(i, j);
		}
	}

	return res;
}

Matrix Matrix::operator-(Matrix n) {
	Matrix res = Matrix(rows_, cols_);

	for (size_t i = 0; i < rows_; i++) {
		for (size_t j = 0; j < cols_; j++) {
			res(i, j) = m_[i][j] - n(i, j);
		}
	}

	return res;
}
