#include "Player.h"

#include "../physics/collider/BoxCollider.h"

Player::Player() {
	collider = new BoxCollider(glm::vec3(1, 2, 1));
	aabb.extents = glm::vec3(1, 2, 1);
}