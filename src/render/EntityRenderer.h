#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include <vector>

#include "../shaders/ShadersDatabase.h"
#include "../player/Camera.h"
#include "../entity/Entity.h"
#include "../world/Sun.h"
#include "fog/Fog.h"

class EntityRenderer {
	std::vector<std::shared_ptr<Entity>> entities;
	Shader* activeShader;

	void updateModelMatrix(const Entity& entity);
	void updateShader(const Camera& camera, const Sun& sun);
	void render(Entity& entity, const Camera* camera = nullptr, bool onlyVisible = false);
public:
	void add(std::shared_ptr<Entity>& entity);
	void renderLights(const Sun& sun);
	void render(const Camera& camera, const Sun& sun);
};

#endif