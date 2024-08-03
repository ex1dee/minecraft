#ifndef DIRECTLIGHT_H
#define DIRECTLIGHT_H

#include "Light.h"

class DirectLight : public Light {
public:
	glm::vec3 direction;

	DirectLight(Shader* FBOShader, const glm::vec3& color, const DFBConfig& DFBconfig = DEFAULT_DFB)
		: Light(FBOShader, color, DFBconfig) {
		direction = glm::vec3(0, -1, 0);
	
		framebuffers[0] = new DepthFramebuffer(FBOShader, DFBconfig);
	}

	DepthFramebuffer& getFramebuffer() { return *framebuffers[0]; }

	void startRender() {
		getFramebuffer().startRender(direction, position);
	}

	void finishRender() {
		getFramebuffer().finishRender();
	}
};

#endif