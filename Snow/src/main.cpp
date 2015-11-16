#include <iostream>
#define GLEW_STATIC
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include <vector>
#include "glm/glm.hpp"

int main() {
	if (!glfwInit())
		exit(1);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "tit", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	while (!glfwWindowShouldClose(window)) {
		glViewport(0, 0, 1280, 720);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4, 0.4, 0.4, 1.0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
}
