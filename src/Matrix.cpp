#include <cstddef>
#include <vector>
#include "Matrix.h"
#include "Vertex.h"

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

Vertex Matrix::operator*(Vertex v) {
	double x = m_[0][0]*v.x + m_[0][1]*v.y + m_[0][2]*v.z + m_[0][3]*v.w;
	double y = m_[1][0]*v.x + m_[1][1]*v.y + m_[1][2]*v.z + m_[1][3]*v.w;
	double z = m_[2][0]*v.x + m_[2][1]*v.y + m_[2][2]*v.z + m_[2][3]*v.w;
	double w = m_[3][0]*v.x + m_[3][1]*v.y + m_[3][2]*v.z + m_[3][3]*v.w;

	return Vertex(x, y, z, w);
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
