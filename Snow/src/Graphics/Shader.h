#pragma once
#include <iostream>
#include <GLEW/glew.h>

class Shader
{
public:
	Shader(const char *vsPath, const char *fsPath, const char* name);
	~Shader(void);

	void init(const char *vsPath, const char *fsPath);

	void bind();		// use the shader vert and frag
	void unbind();		// stop using shader vert and frag

	unsigned int getID() const;

	void uniformVector(const char*, float*);
	void uniformVector(const char*, float, float, float);
	void uniformFloat(const char*, float);
	void uniformTex(const char*, GLuint, unsigned short);

	//glsl program handler
	unsigned int				shaderProgram;

	//vert and fag shaders
	unsigned int				vertShader;
	unsigned int				fragShader;

	const char*					name;


};
