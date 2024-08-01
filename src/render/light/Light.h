#ifndef LIGHT_H
#define LIGHT_H

#include "../DepthFramebuffer.h"
#include "../RenderInfo.h"

class Light {
protected:
	DepthFramebuffer* framebuffer;
public:
	glm::vec3 position;
	glm::vec3 color;

	Light(Shader* FBOShader, const glm::vec3& color)
		: color(color), position(glm::vec3(0)) {
		framebuffer = new DepthFramebuffer(FBOShader);
	}

	~Light() {
		delete framebuffer;
	}

	DepthFramebuffer& getFramebuffer() { return *framebuffer; }

	void finishRender() {
		framebuffer->finishRender();
	}

	virtual void startRender() = 0;
};

#endif