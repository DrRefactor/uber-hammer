#pragma once

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>


class Box {
public:
	GLfloat min_x;
	GLfloat max_x;
	GLfloat min_y;
	GLfloat max_y;
	GLfloat min_z;
	GLfloat max_z;

	const size_t verticesCount = 192;
	const size_t indicesCount = 36;

	Box(GLfloat min_x, GLfloat max_x, GLfloat min_y, GLfloat max_y, GLfloat min_z, GLfloat max_z)
		: min_x(min_x), max_x(max_x), min_y(min_y), max_y(max_y), min_z(min_z), max_z(max_z) {}

	const std::vector<GLfloat> getVertices() {
		std::vector<GLfloat> verts = {
			min_x, max_y, min_z,  -1.000000, 0.000000, 0.000000,   1.000000, 1.000000,  // 1
			min_x, min_y, max_z,  -1.000000, 0.000000, 0.000000,   0.000000, 0.000000,  // 1
			min_x, max_y, max_z,  -1.000000, 0.000000, 0.000000,   1.000000, 0.000000,  // 1

			max_x, max_y, min_z,   0.000000, 0.000000,-1.000000,   0.000000, 1.000000,  //   3
			min_x, min_y, min_z,   0.000000, 0.000000,-1.000000,   1.000000, 0.000000,  //   3
			min_x, max_y, min_z,   0.000000, 0.000000,-1.000000,   0.000000, 0.000000,  //   3

			max_x, max_y, max_z,   1.000000, 0.000000, 0.000000,   1.000000, 0.000000,  //  2
			max_x, min_y, min_z,   1.000000, 0.000000, 0.000000,   0.000000, 1.000000,  //  2
			max_x, max_y, min_z,   1.000000, 0.000000, 0.000000,   1.000000, 1.000000,  //  2

			min_x, max_y, max_z,   0.000000, 0.000000, 1.000000,   0.000000, 0.000000,  //    4
			max_x, min_y, max_z,   0.000000, 0.000000, 1.000000,   1.000000, 1.000000,  //    4
			max_x, max_y, max_z,   0.000000, 0.000000, 1.000000,   0.000000, 1.000000,  //    4

			//bot
			min_x, min_y, min_z,   0.000000,-1.000000, 0.000000,   0.000000, 1.000000,  //     5
			max_x, min_y, max_z,   0.000000,-1.000000, 0.000000,   1.000000, 0.000000,  //     5
			min_x, min_y, max_z,   0.000000,-1.000000, 0.000000,   0.000000, 0.000000,  //     5

			//top
			max_x, max_y, min_z,   0.000000, 1.000000, 0.000000,   0.000000, 1.000000,  //      6
			min_x, max_y, max_z,   0.000000, 1.000000, 0.000000,   1.000000, 0.000000,  //      6
			max_x, max_y, max_z,   0.000000, 1.000000, 0.000000,   0.000000, 0.000000,  //      6

			min_x, min_y, min_z,  -1.000000, 0.000000, 0.000000,   0.000000, 1.000000,  // 1
			max_x, min_y, min_z,   0.000000, 0.000000,-1.000000,   1.000000, 1.000000,  //   3
			max_x, min_y, max_z,   1.000000, 0.000000, 0.000000,   0.000000, 0.000000,  //  2
			min_x, min_y, max_z,   0.000000, 0.000000, 1.000000,   1.000000, 0.000000,  //    4
			max_x, min_y, min_z,   0.000000,-1.000000, 0.000000,   1.000000, 1.000000,  //     5
			min_x, max_y, min_z,   0.000000, 1.000000, 0.000000,   1.000000, 1.000000,  //      6
		};
		return verts;
	}
	const std::vector<GLuint> getIndices() {
		std::vector<GLuint> inds = {
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
			9, 10, 11,
			12, 13, 14,
			15, 16, 17,
			0, 18, 1,
			3, 19, 4,
			6, 20, 7,
			9, 21, 10,
			12, 22, 13,
			15, 23, 16,
		};
		return inds;
	}
};