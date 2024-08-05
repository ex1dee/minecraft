#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray {
public:
	glm::vec3 start;
	glm::vec3 direction;

	Ray(const glm::vec3& start, const glm::vec3& direction)
		: start(start), direction(direction) {

	}
};

#endif