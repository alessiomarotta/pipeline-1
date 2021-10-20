#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:
	double x, y, z, w;

	Vertex() : Vertex(0.0, 0.0, 0.0, 0.0) {}

	Vertex(double x, double y, double z, double w=1.0);

	Vertex operator+(Vertex r);

	Vertex operator-(Vertex r);

	Vertex operator*(double r);

	Vertex operator/(double r);

	double operator*(Vertex r);

	bool operator==(Vertex r);

	double norm();
};

#endif