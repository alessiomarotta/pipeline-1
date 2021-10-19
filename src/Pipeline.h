#ifndef PIPELINE_H
#define PIPELINE_H

#include "Fragment.h"
#include "Triangle.h"

class Pipeline {
	public:
		Pipeline(std::vector<Triangle> triangles);

		std::vector<Triangle> project(double top, double bottom, double left, double right, double near, double far);

		std::vector<Triangle> removeTriangles();

		std::vector<Fragment> rasterize();

	private:
		std::vector<Triangle> triangles_;

		size_t screen_width, screen_height;
};

#endif
