#ifndef PIPELINE_H
#define PIPELINE_H

#include "Triangle.h"

class Pipeline {
	public:
		Pipeline(std::vector<Triangle> triangles);

		std::vector<Triangle> project(double top, double bottom, double left, double right, double near, double far);

		std::vector<Triangle> removeTriangles();
	
	private:
		std::vector<Triangle> triangles_;
};

#endif
