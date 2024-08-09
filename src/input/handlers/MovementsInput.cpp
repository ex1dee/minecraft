#include "MovementsInput.h"

#include "../Input.h"
#include "../../player/Camera.h"

std::unordered_map<int, glm::vec3> MovementsInput::keys;
ZoomHandler MovementsInput::runZoom = ZoomHandler(RUN_ZOOM_TIME_SEC, 0.0f, RUN_MIN_ZOOM);

void MovementsInput::handle(Player* player, float deltaTime) {
	RigidBody* rb = &player->rigidBody;

	Orientation orientation = player->orientation;
	glm::vec3 front = orientation.getMovingFront();
	glm::vec3 right = orientation.getMovingRight();
	float speed = calcSpeed(player);

	check(GLFW_KEY_W, rb, front * speed);
	check(GLFW_KEY_S, rb, -front * speed);
	check(GLFW_KEY_A, rb, -right * speed * PLAYER_SIDE_COEF);
	check(GLFW_KEY_D, rb, right * speed * PLAYER_SIDE_COEF);

	checkJumping(player);
	checkRunZoom(player, deltaTime);

	if (Input::justPressed(GLFW_KEY_F)) {
		player->setFlying(!player->flying);
		keys.clear();
	}

	if (player->flying) {
		check(GLFW_KEY_SPACE, rb, glm::vec3(0, 1, 0) * speed);
		check(GLFW_KEY_LEFT_SHIFT, rb, glm::vec3(0, -1, 0) * speed);
	}
}

float MovementsInput::calcSpeed(Player* player) {
	float speed = player->getWalkSpeed();

	player->sprinting = Input::pressed(GLFW_KEY_LEFT_CONTROL);
	player->sneaking = Input::pressed(GLFW_KEY_LEFT_SHIFT);

	if (player->flying) {
		speed *= PLAYER_FLYING_COEF;
	} else {
		if (player->sneaking) {
			speed *= PLAYER_SNEAKING_COEF;
		} else if (player->sprinting) {
			speed *= PLAYER_SPRINT_COEF;
		}
	}

	return speed;
}

void MovementsInput::check(int key, RigidBody* rigidBody, const glm::vec3& velocity) {
	if (keys.find(key) != keys.end()) {
		if (!Input::pressed(key)) {
			rigidBody->velocity += -keys[key];
			keys.erase(key);
		} else {
			rigidBody->velocity += -keys[key] + velocity;
			keys[key] = velocity;
		}
	} else {
		if (Input::pressed(key)) {
			rigidBody->velocity += velocity;
			keys.emplace(key, velocity);
		}
	}
}

void MovementsInput::checkJumping(Player* player) {
	if (Input::pressed(GLFW_KEY_SPACE)) {
		if (!player->isFlying() && player->isOnGround() && player->rigidBody.velocity.y == 0) {
			player->rigidBody.velocity += glm::vec3(0, 1, 0) * player->getJumpForce();
		}
	}
}

void MovementsInput::checkRunZoom(Player* player, float deltaTime) {
	Camera* camera = player->getCamera();

	if (camera->getZoom() <= 0)
		runZoom.handle(
			player->getCamera(),
			Input::pressed(GLFW_KEY_W) && Input::pressed(GLFW_KEY_LEFT_CONTROL),
			deltaTime
		);
}