#include "Sun.h"

DirectLight* Sun::light;

void Sun::initialize(Shader* FBOShader) {
	light = new DirectLight(FBOShader, glm::vec3(1));
}

void Sun::finalize() {
	delete light;
}

void Sun::setTime(float time, const Player& player) {
	time = glm::radians(time);

	light->direction.x = -sin(time);
	light->direction.y = -cos(time);

	glm::vec3 v = glm::vec3(player.transform.position.x, 0, player.transform.position.z);
	light->position = v - light->direction * (float)CHUNK_H;
}