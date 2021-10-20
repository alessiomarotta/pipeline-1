#ifndef PIPELINE_H
#define PIPELINE_H

#include "Fragment.h"
#include "FragmentShader.h"
#include "Triangle.h"

template<typename target_t>
class Pipeline {
	public:
		void set_camera(double top, double bottom, double left, double right, double near, double far);

		void set_target(target_t *target, size_t width, size_t height);

		void set_shader(FragmentShader<target_t> shader);

		std::vector<Triangle> project();

		std::vector<Triangle> removeTriangles();

		std::vector<Fragment> rasterize();

		void applyShader();

		void render(std::vector<Triangle> triangles);

		// not really part of the class, to be used only for debug
		void show();

	private:
		std::vector<Triangle> triangles_;
		std::vector<Fragment> fragments_;
		double top_, bottom_, left_, right_, near_, far_;

		target_t *screen_;
		size_t screen_width_, screen_height_;
		FragmentShader<target_t> shader_;
};

#endif
