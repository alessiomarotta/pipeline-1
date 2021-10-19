#ifndef PIPELINE_H
#define PIPELINE_H

#include "Fragment.h"
#include "Triangle.h"

class Pipeline {
	public:
		Pipeline(std::vector<Triangle> triangles);

		void set_camera(double top, double bottom, double left, double right, double near, double far);

		void set_target(void *target, size_t width, size_t height);

		std::vector<Triangle> project();

		std::vector<Triangle> removeTriangles();

		std::vector<Fragment> rasterize();

	private:
		std::vector<Triangle> triangles_;
		double top_, bottom_, left_, right_, near_, far_;

		// TODO: use target_t instead of void * for screen
		void *screen_;
		size_t screen_width_, screen_height_;
};

#endif
