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
	const char* getShaderSrc(const char* path); //parses shader file and stores code into a char array
	GLuint createShader(const char* shaderSrc, GLenum shaderType) const; //creates a shader, compiles shader code into it and returns compiled shader
	GLuint createProgram(const GLuint vertexShader, const GLuint fragmentShader) const; //creates program and attaches vertex and fragment shader
	
	
	GLuint						shaderProgram;	
};