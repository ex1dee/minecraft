#ifndef CLOUDSRENDERER_H
#define CLOUDSRENDERER_H

#include "../shaders/ShadersDatabase.h"
#include "../player/Player.h"
#include "../world/Clouds.h"
#include "../world/Sun.h"

class CloudsRenderer {
	Shader* activeShader;

	void updateShader(Camera* camera, const Sun& sun);
public:
	void render(Camera* camera, const Clouds& clouds, const Sun& sun, const Player& player);
};

#endif