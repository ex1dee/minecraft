#include "Sun.h"

#include "World.h"

Sun::Sun(Shader* FBOShader, World* world)
	: world(world) {
	light = new DirectLight(
		FBOShader,
		glm::vec3(1),
		DFBConfig(
			0.0f,
			200.0f,
			65.0f,
			2048.0f
		)
	);

	prevFocus = glm::vec3(WORLD_BORDER, WORLD_BORDER, WORLD_BORDER);
}

Sun::~Sun() {
	delete light;
}

void Sun::setTime(float time, Player& player) {
	float sunAngle = calcAngle(time);

	light->direction.x = -sin(sunAngle);
	light->direction.y = -cos(sunAngle);
	light->direction = glm::normalize(light->direction);

	light->position = getFocus(player) - light->direction * (float)CHUNK_H;
}

float Sun::calcAngle(float time) {
	return glm::radians(time);
}

glm::vec3& Sun::getFocus(Player& player) {
	Chunk* chunk = world->getChunk(player.transform.position);
	if (chunk == nullptr)
		return prevFocus;

	glm::vec3 chunkPos = chunk->getWorldPosition(glm::vec3(8, 0, 8));

	if (glm::distance(chunkPos, prevFocus) > CHANGE_FOCUS_DIST) {
		prevFocus = chunkPos;
	}

	return prevFocus;
}