#include <vector>
#include "Matrix.h"
#include "Pipeline.h"
#include "Triangle.h"

Pipeline::Pipeline(std::vector<Triangle> triangles) {
	triangles_ = triangles;
}

std::vector<Triangle> Pipeline::project(double top, double bottom, double left, double right, double near, double far) {
	std::vector<Triangle> res;

	Matrix proj = Matrix();

	proj(0, 0) = 2.0*near / (right-left);
	proj(0, 2) = (left+right) / (left-right);
	proj(1, 1) = 2.0*near / (bottom-top);
	proj(1, 2) = (top+bottom) / (top-bottom);
	proj(2, 2) = (far+near) / (far-near);
	proj(2, 3) = 2.0*near*far / (near-far);
	proj(3, 2) = 1.0;

	for (Triangle t : triangles_) {
		Vertex a = proj * t.a;
		Vertex b = proj * t.b;
		Vertex c = proj * t.c;

		a = a / a.w;
		b = b / b.w;
		c = c / c.w;

		res.push_back(Triangle(a, b, c));
	}

	return res;
}
