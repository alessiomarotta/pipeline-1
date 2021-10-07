#include <cmath>
#include "Vertex.h"

Vertex::Vertex(double x, double y, double z, double w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vertex Vertex::operator+(Vertex r) {
	return Vertex(x + r.x, y + r.y, z + r.z, w + r.w);
}

Vertex Vertex::operator-(Vertex r) {
	return Vertex(x - r.x, y - r.y, z - r.z, w - r.w);
}

Vertex Vertex::operator*(double r) {
	return Vertex(x * r, y * r, z * r, w * r);
}

Vertex Vertex::operator/(double r) {
	return Vertex(x / r, y / r, z / r, w / r);
}

double Vertex::operator*(Vertex r) {
	return x * r.x + y * r.y + z * r.z + w * r.w;
}

bool Vertex::operator==(Vertex r) {
	return x == r.x && y == r.y && z == r.z && w == r.w;
}

double Vertex::norm() {
	return sqrt(x*x + y*y + z*z + w*w);
}
