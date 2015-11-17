#pragma once
#include <iostream>
#include <GLEW/glew.h>
#include "glm/glm.hpp"

class Shader
{
public:
	Shader(const char *vsPath, const char *fsPath, const char* name);
	~Shader(void);

	void init(const char *vsPath, const char *fsPath);

	void bind();		// use the shader vert and frag
	void unbind();		// stop using shader vert and frag

	unsigned int getID() const;

	void uniformVector(const char* vName, float* data);
	void uniformVector(const char* vName, float dataX, float dataY, float dataZ);
	void uniformFloat(const char* vName, float data);
	void uniformTex(const char* vName, GLuint texData, unsigned short activeTex);
	void uniformMatrix4(const char* vName, glm::mat4 data);
	void inAttrib(const char* vName, GLvoid* offset);

	//glsl program handler
	unsigned int				shaderProgram;

	//vert and fag shaders
	unsigned int				vertShader;
	unsigned int				fragShader;

	const char*					name;


};
