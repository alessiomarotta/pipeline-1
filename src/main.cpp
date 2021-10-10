#include <iostream>
#include "Matrix.h"
#include "Vertex.h"

int main() {
	Matrix a = Matrix(2, 2, std::vector<double> {1.2, 2.5, 3.7, 4.1});
	Matrix b = Matrix(2, 2, std::vector<double> {1.2, 2.5, 3.7, 4.1});
	Matrix c = a + b;

	std::cout << c(0, 0) << ' ' << c(0, 1) << std::endl;
	std::cout << c(1, 0) << ' ' << c(1, 1) << std::endl;

	return 0;
}
