#include "AnimationController.h"


void AnimationController::setFrame(const float t) {
	//DrawableGroup::setFrame(t);
}

AnimationController::~AnimationController() {
}

void AnimationController::draw(const glm::mat4 projection, const glm::mat4 view, const glm::mat4 parentTransformation) {
	glm::mat4 m = parentTransformation * this->transformation_current;

	DrawableGroup::draw(projection, view, m);
}

void LinearAnimationController::setFrame(const float t) {
	glm::float32 transformationFraction = t;
	this->transformation_current = transformation_start + transformationFraction * transformation_delta;
}

LinearAnimationController::LinearAnimationController(const glm::mat4 &to, const glm::mat4 &from) :
	transformation_start(from), transformation_delta(to - from) {
	
	transformation_current = transformation_start;
}

