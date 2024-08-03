#include "Sun.h"

#include "../world/World.h"

DirectLight* Sun::light;
glm::vec3 Sun::prevFocus;

void Sun::initialize(Shader* FBOShader) {
	light = new DirectLight(
		FBOShader,
		glm::vec3(1),
		DFBConfig(
			30.0f,
			150.0f,
			125.0f,
			2048.0f
		)
	);

	light->direction = glm::vec3(0, -1, 0);
	prevFocus = glm::vec3(WORLD_BORDER, WORLD_BORDER, WORLD_BORDER);
}

void Sun::finalize() {
	delete light;
}

void Sun::setTime(float time, Player& player, World* world) {
	time = glm::radians(time);

	light->direction.x = -sin(time);
	light->direction.y = -cos(time);
	
	Chunk* chunk = world->getChunk(player.transform.position);
	glm::vec3 chunkPos = chunk->getWorldPosition(glm::vec3(0, 0, 0));

	if (glm::distance(chunkPos, prevFocus) > CHANGE_FOCUS_DIST) {
		prevFocus = chunkPos;
	}

	light->position = prevFocus - light->direction * (float)CHUNK_H;
}