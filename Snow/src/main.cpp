#include "core/core.h"

int main() {

	Window window;
	Camera camera(window.GetAspectRatio());
	Mesh* mesh = CreateMesh("cube.obj", "cube");
	Shader defaultShader("Shaders/defaultShader.vert", "Shaders/defaultShader.frag", "defaultShader");
	GLuint cubevbo;
	glm::vec4 vertices[36] = {
		glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f), // triangle 1 : begin
		glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),// triangle 1 : end
		glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),// triangle 2 : begin
		glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),// triangle 2 : end
		glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),
		glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),
		glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),
		glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, 0.5f, 1.0f)
	};
	glm::vec4 vcolors[36] = {
		glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0)
	};
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->vertices) + sizeof(vcolors), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(mesh->vertices), &mesh->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(mesh->vertices), sizeof(vcolors), vcolors);
	
	GLuint vPosition = glGetAttribLocation(defaultShader.getID(), "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT,GL_FALSE, 0, (GLvoid*)0);
	
	do {
		window.Clear();

		
		DrawMesh(*mesh, camera, defaultShader);
		
		window.Update();
	} while (!window.Closed());
}
