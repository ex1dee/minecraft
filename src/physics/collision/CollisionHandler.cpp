#include "CollisionHandler.h"

#include "../collider/BoxCollider.h"

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

	glm::vec3 deltaPos = rb->deltaPosition;
	glm::vec3 normal = collision.normal;
	float dot = glm::dot(normal, glm::normalize(deltaPos));
	float dpLen = glm::length(deltaPos);

	if (dpLen == 0 || dot >= 0)
		return;

	rb->deltaPosition += normal * (-dot * dpLen + collision.depth);

	if (collision.normal.y == 1) {
		float velLen = glm::length(rb->newVelocity);

		if (velLen == 0)
			return;

		rb->newVelocity += normal * (-dot * glm::length(rb->newVelocity) + collision.depth);
	}
}