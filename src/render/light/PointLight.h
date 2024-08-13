#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class PointLight : public Light {
	const glm::vec3 faces[6] = {
		{1, 0, 0},
		{-1, 0, 0},
		{0, 0, 1},
		{0, 0, -1},
		{0, 1, 0},
		{0, -1, 0}
	};
public:
	float radius = 1.0f;

	PointLight(Shader& FBOShader, const glm::vec3& color, const DFBConfig& DFBconfig = DEFAULT_DFB)
		: Light(color) {
		for (int i = 0; i < 6; ++i) {
			framebuffers.push_back(new DepthFramebuffer(FBOShader, DFBconfig));
		}
	}

	DepthFramebuffer& getFramebuffer(int i) {
		return *framebuffers[i];
	}

	void startRender(int i) {
		framebuffers[i]->startRender(faces[i], position);
	}

	void finishRender(int i) {
		framebuffers[i]->finishRender();
	}
};

#endif