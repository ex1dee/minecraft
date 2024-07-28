#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
	std::string readShaderCode(const char* path);
	unsigned int createShader(GLenum type, const char* path);
	void createProgram(const char* vertexPath, const char* fragmentPath);
	void shaderiv(unsigned int shader);
	void programiv(unsigned int program);

	unsigned int programID;
	const char* vertexPath;
	const char* fragmentPath;
public:
	Shader() {}
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void use();
	void deleteProgram();
	void setBool(const char* uniform, bool value) const;
	void setInt(const char* uniform, int value) const;
	void setFloat(const char* uniform, float value) const;
	void setMat4(const char* uniform, glm::mat4 value) const;
	void setVec3(const char* uniform, glm::vec3 value) const;
	unsigned int getProgramID();
};

#endif