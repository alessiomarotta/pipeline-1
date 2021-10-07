#include <iostream>
#include "Vertex.h"
#include "Matrix.h"

int main() {
	Vertex a = Vertex(1.0, 2.0, 3.0, 4.0);
	Vertex b = Vertex(3.0, 6.0, 9.0, 12.0);

	Matrix m = Matrix(2, 2, std::valarray<double> {1.2, 2.5, 3.7, 4.1});

	return 0;
}
