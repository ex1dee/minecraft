#ifndef MOVEMENTSINPUT_H
#define MOVEMENTSINPUT_H

#include <unordered_map>

#include "ZoomHandler.h"
#include "../Player.h"

#define RUN_ZOOM_TIME_SEC 0.15f
#define RUN_MIN_ZOOM -15.0f

class MovementsInput {
	static std::unordered_map<int, glm::vec3> keys;
	static ZoomHandler runZoom;

	static void checkRunZoom(Player* player);
	static void checkJumping(Player* player);
	static void check(int key, RigidBody* rigidBody, const glm::vec3& velocity);
	static float calcSpeed(Player* player);
public:
	static void handle(Player* player);
};

#endif