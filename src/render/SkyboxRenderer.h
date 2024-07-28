#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include "../textures/CubeTexture.h"
#include "../shaders/Shader.h"
#include "../player/Camera.h"
#include "Model.h"

class SkyboxRenderer {
	Model model;
	Shader* shader;
	CubeTexture* texture;
	glm::mat4 matModel;

	void loadTexture();
	void makeModel();
public:
	SkyboxRenderer();
	~SkyboxRenderer();

	void setTime(float time);
	void render(Camera& camera);
};

#endif