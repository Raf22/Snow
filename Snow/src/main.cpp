#include "core/core.h"

int main() {

	Window window;
	Camera camera(window.GetAspectRatio());
	Mesh* mesh = CreateMesh("cube.obj", "cube");
	Shader defaultShader("Shaders/defaultShader.vert", "Shaders/defaultShader.frag", "defaultShader");
	SetupMesh(mesh, defaultShader);
	
	do {
		window.Clear();

		DrawMesh(*mesh, camera, defaultShader);
		
		window.Update();
	} while (!window.Closed());
}
