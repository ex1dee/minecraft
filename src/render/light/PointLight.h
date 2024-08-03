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
	float radius;

	PointLight(Shader* FBOShader, const glm::vec3& color, const DFBConfig& DFBconfig = DEFAULT_DFB)
		: Light(FBOShader, color, DFBconfig) {
		radius = 1.0f;

		for (int i = 0; i < 6; ++i) {
			framebuffers[i] = new DepthFramebuffer(FBOShader, DFBconfig);
		}
	}

	DepthFramebuffer& getFramebuffer(int i) {
		return *framebuffers[i];
	}

	void startRender(int i) {
		getFramebuffer(i).startRender(faces[i], position);
	}

	void finishRender(int i) {
		getFramebuffer(i).finishRender();
	}
};

#endif