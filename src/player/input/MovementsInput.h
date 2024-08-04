#ifndef MOVEMENTSINPUT_H
#define MOVEMENTSINPUT_H

#include <unordered_map>

#include "../Player.h"

class MovementsInput {
	static std::unordered_map<int, glm::vec3> keys;

	static void check(int key, RigidBody* rigidBody, const glm::vec3& velocity);
	static void checkJumping(Player* player);
	static float calcSpeed(Player* player);
public:
	static void handle(Player* player);
};

#endif