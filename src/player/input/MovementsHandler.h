#ifndef MOVEMENTSHANDLER_H
#define MOVEMENTSHANDLER_H

#include <unordered_map>

#include "../../window/Events.h"
#include "../Player.h"

class MovementsHandler {
	static std::unordered_map<int, glm::vec3> keys;

	static float calcSpeed(Player* player);
	static void check(int key, RigidBody* rigidBody, const glm::vec3& velocity);
public:
	static void handle(Player* player);
};

#endif