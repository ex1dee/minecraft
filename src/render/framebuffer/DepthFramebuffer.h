#ifndef DEPTHFRAMEBUFFER_H
#define DEPTHFRAMEBUFFER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../world/WorldConstants.h"
#include "../../shaders/Shader.h"
#include "DFBConfig.h"

class DepthFramebuffer {
	Shader* shader;
	DFBConfig config;

	glm::mat4 projection;
	glm::mat4 projView;
	glm::mat4 view;

	unsigned int depthMap;
	unsigned int FBO;

	void genFBO();
	void createDepthMap();
	void createProjection();

	void updateView(const glm::vec3& front, const glm::vec3& position);
	void updateProjView(const glm::vec3& front, const glm::vec3& position);
public:
	DepthFramebuffer() {}
	DepthFramebuffer(Shader* shader, const DFBConfig& config);

	glm::mat4 getProjView() { return projView; }
	unsigned int getDepthMap() { return depthMap; }
	Shader* const getShader() { return shader; }

	void startRender(const glm::vec3& front, const glm::vec3& position);
	void finishRender();
};

#endif