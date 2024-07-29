#include "Shader.h"

#include "../utils/Files.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
	: vertexPath(vertexPath), fragmentPath(fragmentPath) {
	createProgram(vertexPath, fragmentPath);
}

Shader::~Shader() {
	glDeleteProgram(programID);
}

void Shader::use() {
	glUseProgram(programID);
}

void Shader::setBool(const char* uniform, bool value) const {
	glUniform1i(glGetUniformLocation(programID, uniform), value);
}

void Shader::setInt(const char* uniform, int value) const {
	glUniform1i(glGetUniformLocation(programID, uniform), value);
}

void Shader::setFloat(const char* uniform, float value) const {
	glUniform1f(glGetUniformLocation(programID, uniform), value);
}

void Shader::setMat4(const char* uniform, const glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(programID, uniform), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const char* uniform, const glm::vec3& value) const {
	glUniform3f(glGetUniformLocation(programID, uniform), value.x, value.y, value.z);
}

void Shader::setVec4(const char* uniform, const glm::vec4& value) const {
	glUniform4f(glGetUniformLocation(programID, uniform), value.x, value.y, value.z, value.w);
}

unsigned int Shader::getProgramID() {
	return programID;
}

void Shader::createProgram(const char* vertexPath, const char* fragmentPath) {
	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexPath);
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentPath);

	programID = glCreateProgram();

	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	programiv(programID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

unsigned int Shader::createShader(GLenum type, const char* path) {
	std::string sCode = readShaderCode(path);
	const char* code = sCode.c_str();
	unsigned int shader = glCreateShader(type);

	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
	shaderiv(shader);

	return shader;
}

std::string Shader::readShaderCode(const char* path) {
	std::string data;

	try {
		data = Files::read(path);
	} catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_READ\n" << e.what() << "\n";
	}

	return data;
}

void Shader::shaderiv(unsigned int shader) {
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILE\n" << infoLog << "\n";
	}
}

void Shader::programiv(unsigned int program) {
	int success;
	char infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK\n" << infoLog << "\n";
	}
}

void Shader::deleteProgram() {
	glDeleteProgram(programID);
	programID = 0;
}