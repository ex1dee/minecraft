#include "CollisionHandler.h"

#include "../collider/BoxCollider.h"

void CollisionHandler::handle(const Collision& collision, GameObject& obj1, GameObject& obj2) {
	if (!collision.collided)
		return;

	//if (obj1->rigidBody.physicsType == PhysicsType::STATIC)
}

void CollisionHandler::handle(const Collision& collision, GameObject& obj, const Block& block) {
	if (!collision.collided)
		return;

	RigidBody& rb = obj.rigidBody;

	rb.deltaPosition += getProjected(rb.deltaPosition, collision);
	
	if (glm::abs(collision.normal.y) == 1)
		rb.newVelocity += getProjected(rb.newVelocity, collision);
}

glm::vec3 CollisionHandler::getProjected(const glm::vec3& v, const Collision& collision) {
	float eps = glm::dot(collision.normal, v);

	if (eps > 0)
		return glm::vec3(0);

	return collision.normal * (-eps + collision.depth);
}