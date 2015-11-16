#include "Window.h"


Window::Window(int _windowWidth, int _windowHeight) : windowWidth(_windowWidth), windowHeight(_windowHeight) {
	Init();
}

Window::~Window() {
	glfwTerminate();
}

void Window::Init() {
	if (!glfwInit())
		exit(1);
	window = glfwCreateWindow(windowWidth, windowHeight, "window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Window::Clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4, 0.4, 0.4, 1.0);
}


void Window::Update() const{
	glViewport(0, 0, windowWidth, windowHeight);

	glfwPollEvents();
	glfwSwapBuffers(window);
}



