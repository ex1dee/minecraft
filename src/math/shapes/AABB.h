#ifndef AABB_H
#define AABB_H

#include <vector>

#include "../geometry/Transform.h"

class AABB {
public:
	glm::vec3 extents = glm::vec3(1);
	glm::vec3 min = glm::vec3(0);

	AABB() = default;
	AABB(const glm::vec3& min, const glm::vec3& max);

	AABB& operator=(const AABB& other) = default;
	AABB& operator=(AABB&& other) = default;

	std::vector<glm::vec3> getVertices() const;
	void applyTransform(const Transform& transform);
	glm::vec3 getVertexInDirection(const glm::vec3& normal) const;
};

#endif