#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Triangle.h"
#include "Vertex.h"

#include "Pipeline.h"
#include "Pipeline.cpp"

int main() {
	Vertex v1 = Vertex(1.0, -1.0, 1.5);
	Vertex v2 = Vertex(1.0, 1.0, 1.1);
	Vertex v3 = Vertex(-1.0, 1.0, 1.5);
	Vertex v4 = Vertex(-1.0, -1.0, 1.9);

	Triangle t1 = Triangle(v1, v2, v3);
	Triangle t2 = Triangle(v1, v3, v4);

	char screen[150 * 50];

	Pipeline<char> p = Pipeline<char>();
	p.set_camera(-1, 1, -1, 1, 1, 2);
	p.set_target(screen, 150, 50);
	p.render({t1, t2});
	p.show();

	return 0;
}
