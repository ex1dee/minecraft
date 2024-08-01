#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>

struct Collision {
	bool collided;
	glm::vec3 normal;
	float depth;
};

#endif