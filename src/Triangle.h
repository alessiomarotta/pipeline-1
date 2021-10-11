#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vertex.h"

class Triangle {
	public:
		Vertex a;
		Vertex b;
		Vertex c;

		Triangle(Vertex a, Vertex b, Vertex c);
};

#endif
