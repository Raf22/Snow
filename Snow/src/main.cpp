#include "core/core.h"

int main() {
	Window window;
	Camera camera;
	Shader defaultShader("Shaders/defaultShader.vert", "Shaders/defaultShader.frag", "defaultShader");
	Mesh *mesh = CreateMesh("sphere.obj", "asteroid");
	do {
		window.Clear();
		DrawMesh(*mesh, camera, defaultShader);
		//glBegin(GL_TRIANGLES);
		//for (int i = 0; i < mesh->vertices.size(); ++i) {
		//	glNormal3f(mesh->normals[i].x, mesh->normals[i].y, mesh->normals[i].z);
		//	glVertex3f(mesh->vertices[i].x, mesh->vertices[i].y, mesh->vertices[i].z);
		//}
		//glEnd();
		window.Update();
	} while (!window.Closed());
}
