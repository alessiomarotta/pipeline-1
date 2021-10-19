#include <algorithm>
#include <vector>
#include "Fragment.h"
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


std::vector<Triangle> Pipeline::removeTriangles() {
	std::vector<Triangle> res;

	for (Triangle t : triangles_) {
		bool outOfBounds = t.a.x > 1.0 && t.b.x > 1.0 && t.c.x > 1.0;
		outOfBounds |= t.a.y > 1.0 && t.b.y > 1.0 && t.c.y > 1.0;
		outOfBounds |= t.a.z > 1.0 && t.b.z > 1.0 && t.c.z > 1.0;
		outOfBounds |= t.a.x < -1.0 && t.b.x < -1.0 && t.c.x < -1.0;
		outOfBounds |= t.a.y < -1.0 && t.b.y < -1.0 && t.c.y < -1.0;
		outOfBounds |= t.a.z < -1.0 && t.b.z < -1.0 && t.c.z < -1.0;

		if (outOfBounds)
			continue;

		res.push_back(t);
	}

	return res;
}

bool edgeFunction(Vertex v1, Vertex v2, double x, double y) {
	return ((x-v1.x) * (v2.y-v1.y) - (y-v1.y) * (v2.x-v1.x) >= 0);
}

bool insideTriangle(Triangle t, double x, double y) {
	bool res = edgeFunction(t.b, t.a, x, y);
	res &= edgeFunction(t.c, t.b, x, y);
	res &= edgeFunction(t.a, t.c, x, y);

	return res;
}

size_t toPixel(double coord, size_t factor) {
	return (coord+1.0) * (factor-1) / 2.0;
}

double toCartesian(size_t coord, size_t factor) {
	return (coord*2.0) / (factor-1) - 1;
}

double  calculateFragmentZ(Triangle t, double x, double y) {
	double x_p = (t.b.y-t.a.y) * (t.c.z-t.a.z) - (t.c.y-t.a.y) * (t.b.z-t.a.z);
	double y_p = (t.c.x-t.a.x) * (t.b.z-t.a.z) - (t.b.x-t.a.x) * (t.c.z-t.a.z);
	double z_p = (t.b.x-t.a.x) * (t.c.y-t.a.y) - (t.b.y-t.a.y) * (t.c.x-t.a.x);
	double w_p = (-x_p * (t.b.x-t.a.x) - y_p * (t.b.y-t.a.y) - z_p * (t.b.z-t.a.z));

	Vertex p = Vertex(x_p, y_p, z_p, w_p);
	return (-p.x * x - p.y * y - p.w) / p.z;
}

std::vector<Fragment> Pipeline::rasterize() {
	std::vector<Fragment> fragments;

	// TODO: add clamping to avoid rendering fragments outside the view
	for (Triangle t : triangles_) {
		double min_x = toPixel(std::min({t.a.x, t.b.x, t.c.x}), screen_width);
		double min_y = toPixel(std::min({t.a.y, t.b.y, t.c.y}), screen_height);
		double max_x = toPixel(std::max({t.a.x, t.b.x, t.c.x}), screen_width);
		double max_y = toPixel(std::max({t.a.y, t.b.y, t.c.y}), screen_height);

		for (size_t x = min_x; x <= max_x; x++) {
			for (size_t y = min_y; y <= max_y; y++) {
				if (insideTriangle(t, toCartesian(x, screen_width), toCartesian(y, screen_height))) {
					double z = calculateFragmentZ(t, toCartesian(x, screen_width), toCartesian(y, screen_height));
					fragments.push_back(Fragment(x, y, z));
				}
			}
		}
	}

	return fragments;
}
