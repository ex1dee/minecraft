#include "Sun.h"

#include "World.h"

constexpr float SUN_CHANGE_FOCUS_DIST = CHUNK_W * 1.5f;
constexpr float TIME_TO_ANGLE_COEF = 360.0f / (float) TICK_PER_DAY;
constexpr float ANGLE_OFFSET = TIME_TO_ANGLE_COEF * -((float) TICK_PER_DAY / 4.0f);

Sun::Sun(Shader& FBOShader, World& world, std::shared_ptr<Player>& player)
	: world(&world), player(player) {
	light = std::make_unique<DirectLight>(
		FBOShader,
		glm::vec3(1),
		DFBConfig(
			0.0f,
			200.0f,
			150.0f,
			4096.0f
		)
	);

	focus = glm::vec3(WORLD_BORDER, WORLD_BORDER, WORLD_BORDER);

	setTime(0);
}

void Sun::setTime(int time) {
	float sunAngle = calcAngle(time);

	light->direction.x = -sin(sunAngle);
	light->direction.y = -cos(sunAngle);
	light->direction = glm::normalize(light->direction);

	light->position = getFocus() - light->direction * (float)CHUNK_H;
}

float Sun::calcAngle(int time) {
	return glm::radians(TIME_TO_ANGLE_COEF * (float) (time) + ANGLE_OFFSET);
}

glm::vec3& Sun::getFocus() {
	glm::vec3 newFocus = glm::vec3(player->transform.position.x, 0, player->transform.position.z);

	if (glm::distance(newFocus, focus) > SUN_CHANGE_FOCUS_DIST) {
		focus = newFocus;
	}

	return focus;
}