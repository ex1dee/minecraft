#ifndef LIGHT_H
#define LIGHT_H

#include <vector>

#include "../framebuffer/DepthFramebuffer.h"
#include "../framebuffer/DFBConfig.h"

class Light {
protected:
	std::vector<std::unique_ptr<DepthFramebuffer>> framebuffers;
public:
	glm::vec3 position;
	glm::vec3 color;

	Light(const glm::vec3& color)
		: color(color), position(glm::vec3(0)) {
		
	}
};

#endif