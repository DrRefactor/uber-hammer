#include "RotationController.h"
//#include "Model.h"
#define GLEW_STATIC
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "shprogram.h"
#include "Drawable.h"

RotationController::RotationController(float angle, glm::vec3 axis) :
	angle(angle), axis(axis) {
	this->setFrame(0.);
}

void RotationController::setFrame(const float t) {
	glm::mat4 r = glm::mat4(1);
	r = glm::rotate(r, this->angle * t, this->axis);
	this->transformation_current = r;
}

RotationController::~RotationController() { }
