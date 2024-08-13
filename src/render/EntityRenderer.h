#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include <vector>

#include "../shaders/ShadersDatabase.h"
#include "../player/Camera.h"
#include "../entity/Entity.h"
#include "../world/Sun.h"
#include "fog/Fog.h"

class EntityRenderer {
	std::vector<Entity*> entities;
	Shader* activeShader;

	void updateModelMatrix(const Entity& entity);
	void updateShader(const Camera& camera, const Sun& sun, const Fog& fog);
	void render(const Entity& entity, Camera* camera = nullptr, bool onlyVisible = false);
public:
	void add(Entity* entity);
	void renderLights(const Sun& sun);
	void render(const Camera& camera, const Sun& sun, const Fog& fog);
};

#endif