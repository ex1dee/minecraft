#include "Player.h"

#include "../world/World.h"
#include "Camera.h"

Player::Player(Camera& camera)
	: camera(&camera), Entity(PLAYER) {
	
}

void Player::setFlying(bool flying) {
	this->flying = flying;

	rigidBody.setPhysicsType(flying ? PhysicsType::STATIC : PhysicsType::DYNAMIC);
}