#include "Shader.h"



Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	GLuint vertexShader, fragmentShader;

	const char *vertexSrc, *fragmentSrc;
	
	vertexSrc = getShaderSrc(vertexPath);
	fragmentSrc = getShaderSrc(fragmentPath);

	vertexShader = createShader(vertexSrc, GL_VERTEX_SHADER);
	fragmentShader = createShader(fragmentSrc, GL_FRAGMENT_SHADER);

	shaderProgram = createProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


Shader::~Shader() {
	glDeleteShader(this->shaderProgram);
}
const char* Shader::getShaderSrc(const char* path) {
	std::string shaderSrc;
	std::ifstream shaderSrcStream(path, std::ios::in);
	if(shaderSrcStream.is_open()) {
		std::string line = "";
		while(getline(shaderSrcStream, line)) {
			shaderSrc += "\n" + line;
		} 
		shaderSrcStream.close();
	}

	return shaderSrc.c_str();
}

GLuint Shader::createShader(const char* shaderSrc,GLenum shaderType) const {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSrc, nullptr);
	glCompileShader(shader);

	return shader;
}

GLuint Shader::createProgram(const GLuint vertexShader, const GLuint fragmentShader) const {
	GLuint shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);

	return shaderProgramID;
}





