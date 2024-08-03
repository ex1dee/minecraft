#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>
#include <iostream>
class AABB {
public:
	glm::vec3 min = glm::vec3(0);
	glm::vec3 extents = glm::vec3(1);

	AABB() {}
	AABB(const glm::vec3& min, const glm::vec3& max) {
		if (glm::length(min) > glm::length(max)) {
			AABB(max, min);

			return;
		}

		this->min = min;
		this->extents = max - min;
	}

	glm::vec3 getVP(const glm::vec3& normal) const {
		glm::vec3 res = min;

		if (normal.x > 0) {
			res.x += extents.x;
		}
		if (normal.y > 0) {
			res.y += extents.y;
		}
		if (normal.z > 0) {
			res.z += extents.z;
		}

		return res;
	}
};

#endif