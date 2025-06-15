#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>

#include "../math/geometry/Transform.h"
#include "PhysicsType.h"

class RigidBody {
	friend class PhysicsEngine;
	friend class CollisionHandler;
	friend class CollisionDetector;

	glm::vec3 newVelocity = glm::vec3(0);
	glm::vec3 deltaPosition = glm::vec3(0);
	PhysicsType physicsType;
public:
	glm::vec3 force = glm::vec3(0);
	glm::vec3 acceleration = glm::vec3(0);
	glm::vec3 velocity = glm::vec3(0);

	float mass;

	RigidBody(float mass = 1.0f)
		: mass(mass) {}

	PhysicsType getPhysicsType() { return physicsType; }
	glm::vec3 getDeltaPosition() { return deltaPosition; }

	void setPhysicsType(PhysicsType type) {
		this->physicsType = type;

		if (type == PhysicsType::STATIC) {
			acceleration = glm::vec3(0);
			velocity = glm::vec3(0);
		}
	}

	void addForce(const glm::vec3& acceleration) {
		this->force += mass * acceleration;
	}
};

#endif