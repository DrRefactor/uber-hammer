#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

class CameraController {
public:
	void updateView();

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	CameraController(GLFWwindow* window);
private:
	GLFWwindow* window;
	float orbitingAngle = 3.14f / 4;
	float orbitingDistance = 15.f;
	float orbitingHeight = 8.f;

	const float FoV = 45.0f;
	const float cameraRotationSpeed = 3.0f;
	const float verticalSpeed = 10.0f;
	const float cameraDistanceSpeed = 6.f;
	const float maxOrbitingHeight = 20.0f;
	const float minOrbittingHeight = 2.0f;
	const float minOrbittingDistance = 7.f;
	const float maxOrbittingDistance = 25.f;
	const float lightSpeed = 1.f;

	glm::vec3 position = glm::vec3(0, 0, 5);
};