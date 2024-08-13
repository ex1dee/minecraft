#include "DepthFramebuffer.h"

#include "../../math/geometry/Orientation.h"
#include "../../render/Renderer.h"

DepthFramebuffer::DepthFramebuffer(Shader& shader, const DFBConfig& config)
	: shader(&shader), config(config) {

	genFBO();
	createProjection();
	createDepthMap();
}

void DepthFramebuffer::genFBO() {
	GL(glGenFramebuffers(1, &FBO));
}

void DepthFramebuffer::createProjection() {
	if (config.isOrtho)
		projection = glm::ortho(
			-config.orthoSize, 
			config.orthoSize, 
			-config.orthoSize, 
			config.orthoSize, 
			config.orthoNear,
			config.orthoFar
		);
	else
		projection = glm::perspective(
			glm::radians(90.0f),
			1.0f,
			config.perspectiveNear,
			config.perspectiveFar
		);
}

void DepthFramebuffer::createDepthMap() {
	GL(glGenTextures(1, &depthMap));
	GL(glBindTexture(GL_TEXTURE_2D, depthMap));

	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));

	GL(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, FRAMEBUFFER_BORDER_COLLOR));

	GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, config.bufferSize, config.bufferSize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0));

	GL(glBindFramebuffer(GL_FRAMEBUFFER, FBO));
	GL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0));
	GL(glDrawBuffer(GL_NONE));
	GL(glReadBuffer(GL_NONE));
	GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void DepthFramebuffer::startRender(const glm::vec3& front, const glm::vec3& position) {
	updateProjView(front, position);

	shader->use();
	shader->setMat4("projView", projView);
	
	GL(glBindFramebuffer(GL_FRAMEBUFFER, FBO));
	GL(glViewport(0, 0, config.bufferSize, config.bufferSize));
	GL(glClear(GL_DEPTH_BUFFER_BIT));
	GL(glEnable(GL_DEPTH_TEST));

	Renderer::enableCullFace();
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer status: not complete\n";
}

void DepthFramebuffer::finishRender() {
	GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	
	Renderer::disableCullFace();
}

void DepthFramebuffer::updateProjView(const glm::vec3& front, const glm::vec3& position) {
	updateView(front, position);

	projView = projection * view;
}

void DepthFramebuffer::updateView(const glm::vec3& front, const glm::vec3& position) {
	Orientation orientation;
	orientation.update(front);

	view = glm::lookAt(
		position,
		position + front,
		orientation.up
	);
}