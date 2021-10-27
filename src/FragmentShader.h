#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H

#include "Fragment.h"

template<typename target_t>
class FragmentShader {
public:
	target_t apply(Fragment &fragment);
};

template<>
char FragmentShader<char>::apply(Fragment &fragment) {
	// transform the z from [-1, 1] to [0, 1] and decimal expand it
	unsigned int digit = int((fragment.z + 1.0) / 2 * 10);
	return char(digit + '0');
}

#endif