#pragma once
#include <list>
#include <vector>
#define GLEW_STATIC
#include "GLEW/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include <fstream>

typedef struct _mesh {
	_mesh() : scale(glm::vec3(1.0, 1.0, 1.0)), position(glm::vec3(0.0, 0.0, 0.0)), rotX(0.0), rotY(0.0), rotZ(0.0) {}

	std::vector<glm::vec4>		vertices;
	std::vector<glm::vec3>		normals;
	std::vector<glm::vec2>		uvs;

	GLuint						vao, vbo, nbo, tbo;
	const char*					name;
	glm::vec3					position, scale;
	GLfloat						rotX, rotY, rotZ;
	glm::quat					rotation;
}Mesh;


typedef struct _tex {
	GLuint						texID;
	
	const char*					name;
}Tex;

typedef struct _model {

	const char*					name;
	Tex							tex;
	Mesh						mesh;
}Model;