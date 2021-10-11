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

	double top = -1.0;
	double bottom = 1.0;
	double left = -1.0;
	double right = 1.0;
	double near = 1.0;
	double far = 2.0;

	Pipeline p = Pipeline({t1, t2});
	std::vector<Triangle> t = p.project(top, bottom, left, right, near, far);

	std::cout << "t[0].a: " << t[0].a.x << ", " << t[0].a.y << ", " << t[0].a.z << ", " << t[0].a.w << std::endl;
	std::cout << "t[0].b: " << t[0].b.x << ", " << t[0].b.y << ", " << t[0].b.z << ", " << t[0].b.w << std::endl;
	std::cout << "t[0].c: " << t[0].c.x << ", " << t[0].c.y << ", " << t[0].c.z << ", " << t[0].c.w << std::endl;
	std::cout << "t[1].a: " << t[1].a.x << ", " << t[1].a.y << ", " << t[1].a.z << ", " << t[1].a.w << std::endl;
	std::cout << "t[1].b: " << t[1].b.x << ", " << t[1].b.y << ", " << t[1].b.z << ", " << t[1].b.w << std::endl;
	std::cout << "t[1].c: " << t[1].c.x << ", " << t[1].c.y << ", " << t[1].c.z << ", " << t[1].c.w << std::endl;

	return 0;
}
