#include "core/core.h"

int main() {

	Window window;
	Camera camera(window.GetAspectRatio(), glm::vec3(2.0,2.0,1.0));
	Mesh* sphereMesh = CreateMesh("sphere.obj", "cube");
	Shader defaultShader("Shaders/defaultShader.vert", "Shaders/defaultShader.frag", "defaultShader");
	SetupMesh(sphereMesh, defaultShader);
	do {
		window.Clear();

		DrawMesh(*sphereMesh, camera, defaultShader);

		window.Update();
	} while (!window.Closed() && glfwGetKey(window.GetWindowInstance(), GLFW_KEY_ESCAPE) != GLFW_PRESS);
}
