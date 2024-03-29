#include <iostream>
#include <vector>
#include "FragmentShader.h"
#include "Matrix.h"
#include "Triangle.h"
#include "Vertex.h"

#include "Pipeline.h"
#include "Pipeline.cpp"

#define SCREEN_WIDTH 150
#define SCREEN_HEIGHT 50

void initializeScreen(char *screen, size_t width, size_t height) {
	for (size_t x = 0; x < width; x++) {
		for (size_t y = 0; y < height; y++)
			screen[y * width + x] = '.';
	}
}

void show(char *screen, size_t width, size_t height) {
	for (size_t y = 0; y < height; y++) {
		std::cout << std::endl;

		for (size_t x = 0; x < width; x++)
			std::cout << screen[y * width + x];
	}

	std::cout << std::endl;
}

int main() {
	Vertex v1(1.0, -1.0, 1.5);
	Vertex v2(1.0, 1.0, 1.1);
	Vertex v3(-1.0, 1.0, 1.5);
	Vertex v4(-1.0, -1.0, 1.9);

	Triangle t1(v1, v2, v3);
	Triangle t2(v1, v3, v4);
	std::vector<Triangle> triangles = {t1, t2};
	FragmentShader<char> shader;

	char screen[SCREEN_WIDTH * SCREEN_HEIGHT];
	initializeScreen(screen, SCREEN_WIDTH, SCREEN_HEIGHT);

	Pipeline<char> p;
	p.setCamera(-1, 1, -1, 1, 1, 2);
	p.setTarget(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
	p.setShader(shader);
	p.render(triangles);

	show(screen, SCREEN_WIDTH, SCREEN_HEIGHT);

	return 0;
}
