#ifndef DEPTHFRAMEBUFFER_H
#define DEPTHFRAMEBUFFER_H

#include "../../GL/GLHelper.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../world/WorldConstants.h"
#include "../../shaders/Shader.h"
#include "DFBConfig.h"

constexpr float FRAMEBUFFER_BORDER_COLLOR[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

class DepthFramebuffer {
	Shader* shader;
	DFBConfig config;

	glm::mat4 projection;
	glm::mat4 projView;
	glm::mat4 view;

	uint32_t depthMap;
	uint32_t FBO;

	void genFBO();
	void createDepthMap();
	void createProjection();

	void updateView(const glm::vec3& front, const glm::vec3& position);
	void updateProjView(const glm::vec3& front, const glm::vec3& position);
public:
	DepthFramebuffer(Shader& shader, const DFBConfig& config);

	glm::mat4 getProjView() const { return projView; }
	uint32_t getDepthMap() const { return depthMap; }
	Shader& getShader() const { return *shader; }

	void startRender(const glm::vec3& front, const glm::vec3& position);
	void finishRender();
};

#endif