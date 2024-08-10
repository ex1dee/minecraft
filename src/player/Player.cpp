#include "Player.h"

#include "../world/World.h"
#include "Camera.h"

Player::Player(Camera* camera)
	: camera(camera), Entity(PLAYER) {
	
}

bool Player::isEyesInWater() {
	Block* block = world->getBlock(transform.position + type->eyesOffset);

	return block->type->id == WATER;
}

void Player::setFlying(bool flying) {
	this->flying = flying;

	rigidBody.setPhysicsType(flying ? PhysicsType::STATIC : PhysicsType::DYNAMIC);
}