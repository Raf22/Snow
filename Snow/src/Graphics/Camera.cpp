#include "Camera.h"

Camera::Camera(GLfloat aspect, glm::vec3 _position, glm::vec3 _up) : position(_position), up(_up), front(glm::vec3(0.0, 0.0, 0.0)), pitch(0.0f), yaw(0.0f), fov(45.0f), near(0.1f), far(1000.0f) {
	asp = aspect;
	worldUp = glm::vec3(0.0, 1.0, 0.0);
	this->UpdateCameraVectors();
}


void Camera::UpdateCameraVectors() {
	//// Calculate the new Front vector
	////glm::vec3 _front;
	////_front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	////_front.y = sin(glm::radians(this->pitch));
	////_front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	////this->front = glm::normalize(_front);
	//// Also re-calculate the Right and Up vector
	//this->right = (glm::cross(this->front, this->worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	//this->up = (glm::cross(this->right, this->front));
}
