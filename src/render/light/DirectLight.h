#ifndef DIRECTLIGHT_H
#define DIRECTLIGHT_H

#include "Light.h"

class DirectLight : public Light {
public:
	glm::vec3 direction = glm::vec3(0, -1, 0);

	DirectLight(Shader& FBOShader, const glm::vec3& color, const DFBConfig& DFBconfig = DEFAULT_DFB)
		: Light(color) {
		framebuffers.push_back(std::make_unique<DepthFramebuffer>(FBOShader, DFBconfig));
	}

	const DepthFramebuffer& getFramebuffer() const { return *framebuffers[0]; }

	void startRender() const {
		framebuffers[0]->startRender(direction, position);
	}

	void finishRender() const {
		framebuffers[0]->finishRender();
	}
};

#endif