#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Pipeline.h"
#include "Triangle.h"
#include "Vertex.h"

int main() {
	Vertex v1 = Vertex(1.0, -1.0, 1.5);
	Vertex v2 = Vertex(1.0, 1.0, 1.1);
	Vertex v3 = Vertex(-1.0, 1.0, 1.5);
	Vertex v4 = Vertex(-1.0, -1.0, 1.9);

	Triangle t1 = Triangle(v1, v2, v3);
	Triangle t2 = Triangle(v1, v3, v4);

	Pipeline p = Pipeline({t1, t2});
	p.set_camera(-1, 1, -1, 1, 1, 2);

	return 0;
}
