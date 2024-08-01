#include "CollisionHandler.h"
#include <iostream>
void CollisionHandler::handle(const Collision& collision, GameObject* obj1, GameObject* obj2) {
	if (!collision.collided)
		return;

	handle(collision, obj1);
	handle(collision, obj2);
}

void CollisionHandler::handle(const Collision& collision, GameObject* obj) {
	if (!collision.collided)
		return;

	RigidBody* rb = &obj->rigidBody;

	glm::vec3 velocity = rb->newVelocity;
	float velLen = glm::length(velocity);
	float dot = glm::dot(collision.normal, glm::normalize(velocity));

	rb->newVelocity += collision.normal * -dot * velLen;
}