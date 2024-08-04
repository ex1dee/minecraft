#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include "../textures/TextureLoader.h"
#include "../shaders/Shader.h"
#include "../player/Camera.h"
#include "../world/Sun.h"
#include "light/DirectLight.h"
#include "model/Model.h"

class SkyboxRenderer {
	Model model;
	CubeTexture* texture;

	void loadTexture();
	void makeModel();
public:
	SkyboxRenderer();
	~SkyboxRenderer();

	void render(Camera* camera, const Sun& sun);
};

#endif