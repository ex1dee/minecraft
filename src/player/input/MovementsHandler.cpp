#include "MovementsHandler.h"

std::unordered_map<int, glm::vec3> MovementsHandler::keys;

void MovementsHandler::handle(Player* player) {
	RigidBody* rb = &player->rigidBody;

	const Orientation orientation = player->getOrientation();
	glm::vec3 front = orientation.getMovingFront();
	glm::vec3 right = orientation.getMovingRight();
	float speed = calcSpeed(player);

	check(GLFW_KEY_W, rb, front * speed);
	check(GLFW_KEY_S, rb, -front * speed);
	check(GLFW_KEY_A, rb, -right * speed * PLAYER_SIDE_COEF);
	check(GLFW_KEY_D, rb, right * speed * PLAYER_SIDE_COEF);

	checkJumping(player);
}

void MovementsHandler::checkJumping(Player* player) {
	if (Events::pressed(GLFW_KEY_SPACE)) {
		if (!player->isJumping()) {
			player->rigidBody.addVelocity(glm::vec3(0, 1, 0) * player->getJumpForce());
		}
	}
}

float MovementsHandler::calcSpeed(Player* player) {
	float speed = player->getWalkSpeed();

	player->bIsSprinting = Events::pressed(GLFW_KEY_LEFT_CONTROL);
	player->bIsSneaking = Events::pressed(GLFW_KEY_LEFT_SHIFT);

	if (player->bIsSneaking) {
		speed *= PLAYER_SNEAKING_COEF;
	} else if (player->bIsSprinting) {
		speed *= PLAYER_SPRINT_COEF;
	}

	return speed;
}

void MovementsHandler::check(int key, RigidBody* rigidBody, const glm::vec3& velocity) {
	if (keys.find(key) != keys.end()) {
		if (!Events::pressed(key)) {
			rigidBody->addVelocity(-keys[key]);
			keys.erase(key);
		} else {
			rigidBody->addVelocity(-keys[key] + velocity);
			keys[key] = velocity;
		}
	} else {
		if (Events::pressed(key)) {
			rigidBody->addVelocity(velocity);
			keys.emplace(key, velocity);
		}
	}
}