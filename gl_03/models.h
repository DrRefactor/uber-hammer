#pragma once

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Box.h"

const GLfloat table_vertices[] = {
	 // pos							  // normal                       // uv
	 20.000000, 0.000000, 20.000000,  0.0000000, 1.000000, 0.000000,  1.0, 1.0,
	 20.000000, 0.000000,-20.000000,  0.0000000, 1.000000, 0.000000,  1.0, 0.0,
	-20.000000, 0.000000, 20.000000,  0.0000000, 1.000000, 0.000000,  0.0, 1.0,
	-20.000000, 0.000000,-20.000000,  0.0000000, 1.000000, 0.000000,  0.0, 0.0,
};

const GLuint table_indices[] = {
	0, 1, 2,
	3, 2, 1
};

const GLfloat _board_min_x = -8.5;
const GLfloat _board_max_x = 8.5;
const GLfloat _board_min_y = -0.5;
const GLfloat _board_max_y = 0.5;
const GLfloat _board_min_z = -3.5;
const GLfloat _board_max_z = 3.5;

Box boardBox(_board_min_x, _board_max_x, _board_min_y, _board_max_y, _board_min_z, _board_max_z);

const GLfloat _holder_min_x = -0.75;
const GLfloat _holder_max_x = 0.5;
const GLfloat _holder_min_y = 0.5;
const GLfloat _holder_max_y = 2.5;
const GLfloat _holder_min_z = -1.0;
const GLfloat _holder_max_z = -.25;

Box hammerHolderBox(_holder_min_x, _holder_max_x, _holder_min_y, _holder_max_y, _holder_min_z, _holder_max_z);

const GLfloat _mold_min_x = 5.0;
const GLfloat _mold_max_x = 7.0;
const GLfloat _mold_min_y = 0.5;
const GLfloat _mold_max_y = 1;
const GLfloat _mold_max_z = 1.5;
const GLfloat _mold_min_z = -3;

Box moldBox(_mold_min_x, _mold_max_x, _mold_min_y, _mold_max_y, _mold_min_z, _mold_max_z);


const GLfloat mold_base_vertices[] = {
	_mold_max_x, _mold_max_y + 0.01, _mold_max_z,  0.0000000, 1.000000, 0.000000,   0.000000, 0.000000,
	_mold_max_x, _mold_max_y + 0.01, _mold_min_z,  0.0000000, 1.000000, 0.000000,   1.000000, 0.000000,
	_mold_min_x, _mold_max_y + 0.01, _mold_max_z,  0.0000000, 1.000000, 0.000000,   0.000000, 1.000000,
	_mold_min_x, _mold_max_y + 0.01, _mold_min_z,  0.0000000, 1.000000, 0.000000,   1.000000, 1.000000,
};

const GLuint mold_base_indices[] = {
	0, 1, 2,
	3, 2, 1
};

const GLfloat _handle_min_x = -.25;
const GLfloat _handle_max_x = .25;
const GLfloat _handle_min_y = -1.25;
const GLfloat _handle_max_y = 6.25;
const GLfloat _handle_min_z = -.25;
const GLfloat _handle_max_z = .25;

Box hammerHandleBox(_handle_min_x, _handle_max_x, _handle_min_y, _handle_max_y, _handle_min_z, _handle_max_z);


const GLfloat _head_min_x = -1.2;
const GLfloat _head_max_x = 1.2;
const GLfloat _head_min_y = 6.25;
const GLfloat _head_max_y = 7.5;
const GLfloat _head_min_z = -.5;
const GLfloat _head_max_z = .5;
Box hammerHeadBox(_head_min_x, _head_max_x, _head_min_y, _head_max_y, _head_min_z, _head_max_z);