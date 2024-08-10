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

	static float calcSpeed(Player* player, Liquid* liquid);
	static void checkFlying(Player* player, float speed);
	static void checkRunZoom(Player* player, float deltaTime);
	static void checkSwimming(Player* player, Liquid* liquid);
	static void checkJumping(Player* player, Liquid* liquid);
	static void check(int key, RigidBody* rigidBody, const glm::vec3& velocity);
public:
	static void handle(Player* player, float deltaTime);
};

#endif