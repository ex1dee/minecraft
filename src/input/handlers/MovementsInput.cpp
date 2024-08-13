#include "MovementsInput.h"

#include "../../player/Camera.h"
#include "../Input.h"

constexpr float
RUN_ZOOM_TIME_SEC = 0.15f,
RUN_MIN_ZOOM = -15.0f;

std::unordered_map<int, glm::vec3> MovementsInput::keys;
ZoomHandler MovementsInput::runZoom = ZoomHandler(RUN_ZOOM_TIME_SEC, 0.0f, RUN_MIN_ZOOM);

void MovementsInput::handle(Player& player, float deltaTime) {
	Liquid* liquid = player.getLiquidAtObject();
	RigidBody& rb = player.rigidBody;

	Orientation orientation = player.orientation;
	glm::vec3 front = orientation.getMovingFront();
	glm::vec3 right = orientation.getMovingRight();
	float speed = calcSpeed(player, liquid);

	check(GLFW_KEY_W, rb, front * speed);
	check(GLFW_KEY_S, rb, -front * speed);
	check(GLFW_KEY_A, rb, -right * speed * PLAYER_SIDE_COEF);
	check(GLFW_KEY_D, rb, right * speed * PLAYER_SIDE_COEF);

	checkJumping(player, liquid);
	checkRunZoom(player, deltaTime);
	checkSwimming(player, liquid);
	checkFlying(player, speed);
}

void MovementsInput::checkFlying(Player& player, float speed) {
	RigidBody& rb = player.rigidBody;

	if (Input::justPressed(GLFW_KEY_F)) {
		player.setFlying(!player.flying);

		rb.velocity = glm::vec3(0);
		keys.clear();
	}

	if (player.flying) {
		check(GLFW_KEY_SPACE, rb, glm::vec3(0, 1, 0) * speed);
		check(GLFW_KEY_LEFT_SHIFT, rb, glm::vec3(0, -1, 0) * speed);
	}
}

void MovementsInput::checkSwimming(Player& player, Liquid* liquid) {
	RigidBody& rb = player.rigidBody;

	if (liquid != nullptr && !player.flying) {
		if (Input::pressed(GLFW_KEY_SPACE)) {
			rb.velocity.y = player.getJumpForce() * PLAYER_INLIQUID_JUMP_COEF;
			keys.emplace(GLFW_KEY_SPACE, rb.velocity);
		} else if (keys.find(GLFW_KEY_SPACE) != keys.end()) {
			rb.velocity.y -= keys[GLFW_KEY_SPACE].y;
			keys.erase(GLFW_KEY_SPACE);
		}
	}
}

float MovementsInput::calcSpeed(Player& player, Liquid* liquid) {
	float speed = player.getWalkSpeed();

	player.sprinting = Input::pressed(GLFW_KEY_LEFT_CONTROL);
	player.sneaking = Input::pressed(GLFW_KEY_LEFT_SHIFT);

	if (player.flying) {
		speed *= PLAYER_FLYING_COEF;
	} else if (liquid != nullptr) {
		speed *= PLAYER_INLIQUID_SWIM_COEF * liquid->getSpeedCoef();
	} else if (player.sneaking) {
		speed *= PLAYER_SNEAKING_COEF;
	}
	
	if (player.sprinting) {
		speed *= PLAYER_SPRINT_COEF;
	}

	return speed;
}

void MovementsInput::checkJumping(Player& player, Liquid* liquid) {
	if (player.isFlying())
		return;

	RigidBody& rb = player.rigidBody;

	if (Input::pressed(GLFW_KEY_SPACE)) {
		if (liquid == nullptr && player.isOnGround() && rb.velocity.y == 0) {
			rb.velocity += glm::vec3(0, 1, 0) * player.getJumpForce();
		}
	}
}

void MovementsInput::check(int key, RigidBody& rigidBody, const glm::vec3& velocity) {
	if (keys.find(key) != keys.end()) {
		if (!Input::pressed(key)) {
			rigidBody.velocity += -keys[key];
			keys.erase(key);
		} else {
			rigidBody.velocity += -keys[key] + velocity;
			keys[key] = velocity;
		}
	} else {
		if (Input::pressed(key)) {
			rigidBody.velocity += velocity;
			keys.emplace(key, velocity);
		}
	}
}

void MovementsInput::checkRunZoom(Player& player, float deltaTime) {
	Camera& camera = player.getCamera();

	if (camera.getZoom() <= 0)
		runZoom.handle(
			player.getCamera(),
			Input::pressed(GLFW_KEY_W) && Input::pressed(GLFW_KEY_LEFT_CONTROL),
			deltaTime
		);
}