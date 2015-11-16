#pragma once
#include <iostream>
#define GLEW_STATIC
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

class Window {
public:
	Window(int _windowWidth = 1280, int _windowHeight = 720);
	~Window();

	void Clear() const;
	void Update() const;

	inline bool Closed() const { return glfwWindowShouldClose(window); }

	GLFWwindow* GetWindowInstance() const { return window; }
private:
	void Init();

	GLFWwindow* 				window;
	GLint						windowWidth, windowHeight;
};