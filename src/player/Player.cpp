#include "Player.h"

#include "Camera.h"

Player::Player(Camera* camera)
	: camera(camera), Entity(PLAYER) {
	
}

bool Player::isJumping() {
	return glm::abs(rigidBody.velocity.y) > 0.00001f;
}