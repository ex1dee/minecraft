#include "Player.h"

#include "../physics/collider/BoxCollider.h"
#include "Camera.h"

Player::Player(Camera* camera)
	: camera(camera) {
	Transform transform;
	transform.position = glm::vec3(-0.5f, 0, -0.5f);
	collider = new BoxCollider(glm::vec3(1, 2, 1), transform);

	aabb.extents = glm::vec3(1, 2, 1);
}

bool Player::isJumping() {
	return glm::abs(rigidBody.velocity.y) > 0.00001f;
}

const Orientation& Player::getOrientation() { 
	return camera->getOrientation();
}