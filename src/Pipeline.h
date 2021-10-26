#ifndef PIPELINE_H
#define PIPELINE_H

#include "Fragment.h"
#include "FragmentShader.h"
#include "Triangle.h"

template<typename target_t>
class Pipeline {
public:
	void setCamera(double top, double bottom, double left, double right, double near, double far);

	void setTarget(target_t *target, size_t width, size_t height);

	void setShader(FragmentShader<target_t> &shader);

	void render(std::vector<Triangle> &triangles);

private:
	void project();

	void removeTriangles();

	void rasterize();

	void applyShader();

	std::vector<Triangle> triangles_;
	std::vector<Fragment> fragments_;
	double top_, bottom_, left_, right_, near_, far_;

	target_t *screen_;
	size_t screen_width_, screen_height_;
	FragmentShader<target_t> shader_;
};

#endif