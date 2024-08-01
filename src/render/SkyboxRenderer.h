#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include "../textures/BasicTexture.h"
#include "../textures/CubeTexture.h"
#include "../shaders/Shader.h"
#include "../player/Camera.h"
#include "light/DirectLight.h"
#include "Model.h"

class SkyboxRenderer {
	Model model;
	Shader* skyboxShader;
	CubeTexture* texture;

	void loadTexture();
	void makeModel();
public:
	SkyboxRenderer();
	~SkyboxRenderer();

	void render(Camera& camera, DirectLight* sunLight);
};

#endif