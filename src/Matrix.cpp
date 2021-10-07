#include <valarray>
#include "Matrix.h"

Matrix::Matrix(size_t rows, size_t cols, std::valarray<double> m) : rows_(rows), cols_(cols), m_(m) {}
