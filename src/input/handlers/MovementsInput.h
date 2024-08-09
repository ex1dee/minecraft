#ifndef MOVEMENTSINPUT_H
#define MOVEMENTSINPUT_H

#include <unordered_map>

#include "../../player/Player.h"
#include "ZoomHandler.h"

#define RUN_ZOOM_TIME_SEC 0.15f
#define RUN_MIN_ZOOM -15.0f

class MovementsInput {
	static std::unordered_map<int, glm::vec3> keys;
	static ZoomHandler runZoom;

	static float calcSpeed(Player* player);
	static void checkJumping(Player* player);
	static void checkRunZoom(Player* player, float deltaTime);
	static void check(int key, RigidBody* rigidBody, const glm::vec3& velocity);
public:
	static void handle(Player* player, float deltaTime);
};

#endif