#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include "../textures/TextureLoader.h"
#include "../shaders/Shader.h"
#include "../player/Camera.h"
#include "../world/Sun.h"
#include "light/DirectLight.h"
#include "model/Model.h"
#include "fog/Fog.h"

class SkyboxRenderer {
	std::shared_ptr<CubeTexture> texture;
	Model model;

	void loadTexture();
	void makeModel();
public:
	SkyboxRenderer();

	void render(const Camera& camera, const Sun& sun, const Fog& fog);
};

#endif