#include "core/core.h"

int main() {

	Window window;
	Camera camera(window.GetAspectRatio(), glm::vec3(2.0, 2.0, 1.0));
	Mesh* sphereMesh = CreateMesh("sphere.obj", "sphere");
	Shader defaultShader("Shaders/defaultShader.vert", "Shaders/defaultShader.frag", "defaultShader");
	SetupMesh(sphereMesh, defaultShader);
	do {
		window.Clear();

		DrawMesh(*sphereMesh, camera, defaultShader);
		camera.front = sphereMesh->position;
		sphereMesh->rotY -= 0.016;
		{
			if (glfwGetKey(window.GetWindowInstance(), GLFW_KEY_W) == GLFW_PRESS) {
				sphereMesh->position.x -= 0.16;
			}
			else if (glfwGetKey(window.GetWindowInstance(), GLFW_KEY_S) == GLFW_PRESS) {
				sphereMesh->position.x += 0.16;
			}
			if (glfwGetKey(window.GetWindowInstance(), GLFW_KEY_A) == GLFW_PRESS) {
				sphereMesh->position.z += 0.16;
			}
			else if (glfwGetKey(window.GetWindowInstance(), GLFW_KEY_D) == GLFW_PRESS) {
				sphereMesh->position.z -= 0.16;
			}
		}
		window.Update();
	} while (!window.Closed() && glfwGetKey(window.GetWindowInstance(), GLFW_KEY_ESCAPE) != GLFW_PRESS);
	delete sphereMesh;
}
