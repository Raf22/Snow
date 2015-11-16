#include "Shader.h"

// Forward definition of a utility function
static char* readTextFromFile(const char *fileName);

Shader::Shader(const char *vsFile, const char *fsFile, const char* name) : name(name) {
	init(vsFile, fsFile);
}

Shader::~Shader(void) {
	glDetachShader(shaderProgram, vertShader);
	glDetachShader(shaderProgram, fragShader);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	glDeleteProgram(shaderProgram);
}

void Shader::init(const char *vsFile, const char *fsFile) {

	GLint result = 0;
	GLchar error[1024] = { 0 };

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	const char *vsText = readTextFromFile(vsFile);
	glShaderSource(vertShader, 1, &vsText, 0);
	glCompileShader(vertShader);
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderInfoLog(vertShader, sizeof(error), NULL, error);
		std::cerr << "Error Compiling Shader: " << error << std::endl;
	}
	else printf("Compiled!\n");

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fsText = readTextFromFile(fsFile);
	glShaderSource(fragShader, 1, &fsText, 0);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderInfoLog(vertShader, sizeof(error), NULL, error);
		std::cerr << "Error Compiling Shader: " << error << std::endl;
	}
	else printf("Compiled!\n");

	shaderProgram = glCreateProgram();

	// attaching the vertex and fragment shaders to the program id
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);

	// linking the programs
	glLinkProgram(shaderProgram);
}

void Shader::bind() {
	glUseProgram(shaderProgram);
}

void Shader::unbind() {
	glUseProgram(0);
}

unsigned int Shader::getID() const {
	return shaderProgram;
}

static char* readTextFromFile(const char *fileName) {

	std::cout << "\t" << fileName << "... \t";

	static char* text;

	if (fileName != NULL) {
		FILE *file;
		fopen_s(&file, fileName, "rt");

		if (file != NULL) {
			fseek(file, 0, SEEK_END);
			int count = ftell(file);
			rewind(file);
			if (count > 0) {
				text = (char*)malloc(sizeof(char) * (count + 1));
				count = fread(text, sizeof(char), count, file);
				text[count] = '\0';
			}
			fclose(file);
		}
		else {
			printf("ERROR: Could not find file. %s", fileName);
		}
	}

	return text;
}

void Shader::uniformVector(const char* varName, float *data) {
	GLint loc = glGetUniformLocation(shaderProgram, varName);
	glUniform3fv(loc, 1, data);
}

void Shader::uniformVector(const char* varName, float x, float y, float z) {
	float temp[3] = { x, y, z };
	GLint loc = glGetUniformLocation(shaderProgram, varName);
	glUniform3fv(loc, 1, temp);
}

void Shader::uniformFloat(const char* varName, float data) {
	GLint loc = glGetUniformLocation(shaderProgram, varName);
	glUniform1f(loc, data);
}

void Shader::uniformTex(const char* varName, GLuint data, unsigned short activeTexture) {

	switch (activeTexture)
	{
	case 0:
		glActiveTexture(GL_TEXTURE0);
		break;
	case 1:
		glActiveTexture(GL_TEXTURE1);
		break;
	case 2:
		glActiveTexture(GL_TEXTURE2);
		break;
	default:
		glActiveTexture(GL_TEXTURE0);
		break;
	}

	glBindTexture(GL_TEXTURE_2D, data);
	GLuint loc = glGetUniformLocation(getID(), varName);
	glUniform1i(loc, activeTexture);
}




