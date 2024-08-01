#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>

#include "../math/Transform.h"

const glm::vec3 GRAVITY = glm::vec3(0.0f, -9.8f, 0.0f);

class RigidBody {
public:
	glm::vec3 force = glm::vec3(0);
	glm::vec3 acceleration = glm::vec3(0);
	glm::vec3 velocity = glm::vec3(0);

	glm::vec3 newPosition = glm::vec3(0);
	glm::vec3 newVelocity = glm::vec3(0);

	bool updateEveryTick;
	bool physics;
	float mass;

	RigidBody(bool physics, bool updateEveryTick, float mass)
		: physics(physics), updateEveryTick(updateEveryTick), mass(mass) { }

	void addForce(const glm::vec3& acceleration) {
		force += mass * acceleration;
	}
};

#endif