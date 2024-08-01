#include "DepthFramebuffer.h"

#include <glad/glad.h>

#include "../math/Orientation.h"

DepthFramebuffer::DepthFramebuffer(Shader* shader)
	: shader(shader), width(FB_SIZE), height(FB_SIZE) {

	genFBO();
	createProjection();
	createDepthMap();
}

void DepthFramebuffer::genFBO() {
	glGenFramebuffers(1, &FBO);
}

void DepthFramebuffer::createProjection() {
	projection = glm::ortho(-FB_ORTHO_SIZE, FB_ORTHO_SIZE, -FB_ORTHO_SIZE, FB_ORTHO_SIZE, FB_ORTHO_NEAR, FB_ORTHO_FAR);
}

void DepthFramebuffer::createDepthMap() {
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DepthFramebuffer::startRender(const glm::vec3& front, const glm::vec3& position) {
	updateProjView(front, position);

	shader->use();
	shader->setMat4("projView", projView);
	
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, width, height);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer status: not complete\n";
}

void DepthFramebuffer::finishRender() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT);
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

void DepthFramebuffer::updateProjView(const glm::vec3& front, const glm::vec3& position) {
	updateView(front, position);

	projView = projection * view;
}