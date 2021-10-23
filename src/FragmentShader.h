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
	return '0' + fragment.z * 10;
}

#endif