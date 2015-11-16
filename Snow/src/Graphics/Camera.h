#pragma once
#include "GLEW/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 GetViewMatrix() const { return glm::lookAt(this->position, this->position + this->front, this->up); }
	
	
	glm::vec3					position, front, up, right, worldUp;
	GLfloat						pitch, yaw;
private:
	void UpdateCameraVectors();
};