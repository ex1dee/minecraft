#ifndef FOG_H
#define FOG_H

#include <glm/glm.hpp>

#include "../../shaders/Shader.h"
#include "FogType.h"

class Fog {
public:
	FogType type;
	glm::vec4 color;
	float density;
	float zStart;
	float zEnd;

	bool enabled = false;

	Fog() {}
	Fog(const glm::vec4& color)
		: type(FogType::LINEAR), enabled(true), color(color), zStart(zStart), zEnd(zEnd) {}
	Fog(const glm::vec4& color, float density) 
		: type(FogType::EXPONENTIAL), enabled(true), color(color), density(density) {}

	void addToShader(Shader* shader) const {
		shader->setBool("fog.enabled", enabled);

		if (!enabled)
			return;

		shader->setVec4("fog.color", color);
		shader->setInt("fog.type", type);

		if (type == FogType::LINEAR) {
			shader->setFloat("fog.zStart", zStart);
			shader->setFloat("fog.zEnd", zEnd);
		} else {
			shader->setFloat("fog.density", density);
		}
	}
};

#endif