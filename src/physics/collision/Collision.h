#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>

struct Collision {
	glm::vec3 normal;
	bool collided;
	float depth;
};

#endif