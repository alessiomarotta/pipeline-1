#include <algorithm>
#include <vector>
#include "Fragment.h"
#include "FragmentShader.h"
#include "Matrix.h"
#include "Pipeline.h"
#include "Triangle.h"

template<typename target_t>
void Pipeline<target_t>::setCamera(double top, double bottom, double left, double right, double near, double far) {
	top_ = top;
	bottom_ = bottom;
	left_ = left;
	right_ = right;
	near_ = near;
	far_ = far;
}

template<typename target_t>
void Pipeline<target_t>::setTarget(target_t *target, size_t width, size_t height) {
	screen_ = target;
	screen_width_ = width;
	screen_height_ = height;
}

template<typename target_t>
void Pipeline<target_t>::setShader(FragmentShader<target_t> &shader) {
	shader_ = shader;
}

template<typename target_t>
void Pipeline<target_t>::project() {
	Matrix proj = Matrix();

	// set perspective projection matrix
	proj(0, 0) = 2.0*near_ / (right_-left_);
	proj(0, 2) = (left_+right_) / (left_-right_);
	proj(1, 1) = 2.0*near_ / (bottom_-top_);
	proj(1, 2) = (top_+bottom_) / (top_-bottom_);
	proj(2, 2) = (far_+near_) / (far_-near_);
	proj(2, 3) = 2.0*near_*far_ / (near_-far_);
	proj(3, 2) = 1.0;

	for (Triangle &t : triangles_) {
		Vertex a = proj * t.a;
		Vertex b = proj * t.b;
		Vertex c = proj * t.c;

		// normalize coordinates
		t.a = a / a.w;
		t.b = b / b.w;
		t.c = c / c.w;
	}
}

bool outOfBounds(Triangle t) {
	bool res = t.a.x > 1.0 && t.b.x > 1.0 && t.c.x > 1.0;
	res |= t.a.y > 1.0 && t.b.y > 1.0 && t.c.y > 1.0;
	res |= t.a.z > 1.0 && t.b.z > 1.0 && t.c.z > 1.0;
	res |= t.a.x < -1.0 && t.b.x < -1.0 && t.c.x < -1.0;
	res |= t.a.y < -1.0 && t.b.y < -1.0 && t.c.y < -1.0;
	res |= t.a.z < -1.0 && t.b.z < -1.0 && t.c.z < -1.0;

	return res;
}

// remove triangles completely outside of the current view
template<typename target_t>
void Pipeline<target_t>::removeTriangles() {
	triangles_.erase(
		std::remove_if(triangles_.begin(), triangles_.end(),
			[](auto &t) {return outOfBounds(t);} ),
		triangles_.end());
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

double calculateFragmentZ(Triangle t, double x, double y) {
	// calculate the plane passing through t
	double x_p = (t.b.y-t.a.y) * (t.c.z-t.a.z) - (t.c.y-t.a.y) * (t.b.z-t.a.z);
	double y_p = (t.b.z-t.a.z) * (t.c.x-t.a.x) - (t.c.z-t.a.z) * (t.b.x-t.a.x);
	double z_p = (t.b.x-t.a.x) * (t.c.y-t.a.y) - (t.c.x-t.a.x) * (t.b.y-t.a.y);
	double w_p = (-x_p*t.a.x - y_p*t.a.y - z_p*t.a.z);

	return (-x_p*x - y_p*y - w_p) / z_p;
}

bool fragmentCompare(const Fragment &a, const Fragment &b) {
	return a.x == b.x ? a.y <= b.y : a.x <= b.x;
}

void zBuffering(std::vector<Fragment> &fragments) {
	std::sort(fragments.begin(), fragments.end(), fragmentCompare);

	if (fragments.size() == 0)
		return;

	for (size_t i = 0; i < fragments.size()-1; i++) {
		while (i < fragments.size()-1 && fragments[i].x == fragments[i+1].x && fragments[i].y == fragments[i+1].y) {
			if (fragments[i].z > fragments[i+1].z)
				fragments.erase(fragments.begin() + i);

			else
				fragments.erase(fragments.begin() + i + 1);
		}
	}
}

template<typename target_t>
void Pipeline<target_t>::rasterize() {
	for (Triangle &t : triangles_) {
		// calculate bounding box coordinates
		size_t min_x = toPixel(std::min({t.a.x, t.b.x, t.c.x}), screen_width_);
		size_t min_y = toPixel(std::min({t.a.y, t.b.y, t.c.y}), screen_height_);
		size_t max_x = toPixel(std::max({t.a.x, t.b.x, t.c.x}), screen_width_);
		size_t max_y = toPixel(std::max({t.a.y, t.b.y, t.c.y}), screen_height_);

		// clamp bounding box to screen size
		min_x = std::max(min_x, (size_t) 0);
		min_y = std::max(min_y, (size_t) 0);
		max_x = std::min(max_x, screen_width_-1);
		max_y = std::min(max_y, screen_height_-1);

		for (size_t x = min_x; x <= max_x; x++) {
			for (size_t y = min_y; y <= max_y; y++) {
				if (insideTriangle(t, toCartesian(x, screen_width_), toCartesian(y, screen_height_))) {
					double z = calculateFragmentZ(t, toCartesian(x, screen_width_), toCartesian(y, screen_height_));
					fragments_.push_back(Fragment(x, y, z));
				}
			}
		}
	}

	zBuffering(fragments_);
}

template<typename target_t>
void Pipeline<target_t>::applyShader() {
	for (Fragment f : fragments_)
		screen_[f.y * screen_width_ + f.x] = shader_.apply(f);
}

template<typename target_t>
void Pipeline<target_t>::render(std::vector<Triangle> &triangles) {
	triangles_ = triangles;

	project();
	removeTriangles();
	rasterize();
	applyShader();
}
