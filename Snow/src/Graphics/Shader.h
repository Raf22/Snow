#pragma once

#include "GLEW/glew.h"
#include <fstream>
#include <iostream>
#include <string>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void useShaderProgram() const { glUseProgram(this->shaderProgram); }

	const char*					name;
private:
	const char* getShaderSrc(const char* path);
	GLuint createShader(const char* shaderSrc, GLenum shaderType) const;
	GLuint createProgram(const GLuint vertexShader, const GLuint fragmentShader) const;
	
	
	GLuint						shaderProgram;	
};