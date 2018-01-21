#include "CameraController.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

extern float lightIntensity;
extern glm::vec3 lightPosition;

void CameraController::updateView() {
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		orbitingAngle += 1.f * deltaTime * cameraRotationSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		orbitingAngle -= 1.f * deltaTime * cameraRotationSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_UP)) {
		const float newHeight = orbitingHeight + deltaTime * verticalSpeed;
		orbitingHeight = newHeight > maxOrbitingHeight ? maxOrbitingHeight : newHeight;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		const float newHeight = orbitingHeight - deltaTime * verticalSpeed;
		orbitingHeight = newHeight < minOrbittingHeight ? minOrbittingHeight : newHeight;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		const float newDistance = orbitingDistance + deltaTime * cameraDistanceSpeed;
		orbitingDistance = newDistance > maxOrbittingDistance ? maxOrbittingDistance : newDistance;
	}
	if (glfwGetKey(window, GLFW_KEY_W)) {
		const float newDistance = orbitingDistance - deltaTime * cameraDistanceSpeed;
		orbitingDistance = newDistance < minOrbittingDistance ? minOrbittingDistance : newDistance;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		lightIntensity += 20 * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		lightIntensity -= 20 * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		lightPosition.y += deltaTime * lightSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		lightPosition.y -= deltaTime * lightSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		lightPosition.z += deltaTime * lightSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		lightPosition.z -= deltaTime * lightSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		lightPosition.x += deltaTime * lightSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		lightPosition.x -= deltaTime * lightSpeed;
	}

	position = glm::vec3(
		cos(orbitingAngle) * orbitingDistance,
		orbitingHeight,
		sin(orbitingAngle) * orbitingDistance
	);
	glm::vec3 direction = glm::vec3(4, 3., 0) - position;
	direction = glm::normalize(direction);
	glm::vec3 up = glm::vec3(0, 1, 0);

	projectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

	viewMatrix = glm::lookAt(position, position + direction, up);

	lastTime = currentTime;
}

CameraController::CameraController(GLFWwindow* window) : window(window) {
}