#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>

#include "../math/geometry/Transform.h"

const glm::vec3 GRAVITY = glm::vec3(0.0f, -50.0f, 0.0f);

class RigidBody {
public:
	glm::vec3 force = glm::vec3(0);
	glm::vec3 acceleration = glm::vec3(0);
	glm::vec3 velocity = glm::vec3(0);

	glm::vec3 newVelocity = glm::vec3(0);
	glm::vec3 deltaPosition = glm::vec3(0);

	bool physics;
	float mass;

	RigidBody() {}

	void addVelocity(const glm::vec3& velocity) {
		this->velocity += velocity;
	}

	void addGravity() {
		addForce(GRAVITY);
	}

	void addForce(const glm::vec3& acceleration) {
		force += mass * acceleration;
	}
};

#endif