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
	unsigned int digit = int((fragment.z + 1.0) * 10 / 2);
	return char(digit + '0');
}

#endif