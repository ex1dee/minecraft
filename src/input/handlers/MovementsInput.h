#ifndef MOVEMENTSINPUT_H
#define MOVEMENTSINPUT_H

#include <unordered_map>

#include "../../player/Player.h"
#include "ZoomHandler.h"

class MovementsInput {
	static std::unordered_map<int, glm::vec3> keys;
	static ZoomHandler runZoom;

	static bool isWalkKeyPressed();
	static float calcSpeed(Player& player, Liquid* const liquid);
	static void playWalkingSound(Player& player);
	static void checkFlying(Player& player, float speed);
	static void checkRunZoom(Player& player, float deltaTime);
	static void playWalkingAnimation(Player& player, float speed);
	static void checkJumping(Player& player, Liquid* const liquid);
	static void checkSwimming(Player& player, Liquid* const liquid);
	static void check(int key, RigidBody* const rigidBody, const glm::vec3& velocity);
public:
	static void handle(Player& player, float deltaTime);
};

#endif