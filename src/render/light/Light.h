#ifndef LIGHT_H
#define LIGHT_H

#include <array>

#include "../framebuffer/DepthFramebuffer.h"
#include "../RenderInfo.h"
#include "../framebuffer/DFBConfig.h"

class Light {
protected:
	std::array<DepthFramebuffer*, 6> framebuffers;
public:
	glm::vec3 position;
	glm::vec3 color;

	Light(Shader* FBOShader, const glm::vec3& color, const DFBConfig& DFBconfig = DEFAULT_DFB)
		: color(color), position(glm::vec3(0)) {
		
	}

	~Light() {
		for (DepthFramebuffer* framebuffer : framebuffers) {
			delete framebuffer;
		}
	}
};

#endif