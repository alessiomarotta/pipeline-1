#ifndef FRAGMENT_H
#define FRAGMENT_H

#include <cstddef>

class Fragment {
public:
	size_t x, y;
	double z;

	Fragment() : Fragment(0, 0, 0.0) {}

	Fragment(size_t x, size_t y, double z);
};

#endif