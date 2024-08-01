#ifndef DIRECTLIGHT_H
#define DIRECTLIGHT_H

#include "Light.h"

class DirectLight : public Light {
public:
	glm::vec3 direction;

	DirectLight(Shader* FBOShader, const glm::vec3& color)
		: Light(FBOShader, color) {
		direction = glm::vec3(0, -1, 0);
	}

	void startRender() override {
		framebuffer->startRender(direction, position);
	}
};

#endif