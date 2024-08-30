#include "AABB.h"

AABB::AABB(const glm::vec3& min, const glm::vec3& max) {
	this->min = min;
	this->extents = max - min;
}

glm::vec3 AABB::getVertexInDirection(const glm::vec3& normal) const {
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

void AABB::updateTransform(const Transform& transform) {
	min = transform.position;
	extents *= transform.scale;
}

std::vector<glm::vec3> AABB::getVertices() const {
	std::vector<glm::vec3> vertices {
		{min.x,			    min.y,			   min.z},
		{min.x + extents.x, min.y,			   min.z},
		{min.x,				min.y + extents.y, min.z},
		{min.x,				min.y,			   min.z + extents.z},
		{min.x + extents.x, min.y + extents.y, min.z + extents.z},
		{min.x + extents.x, min.y,			   min.z + extents.z},
		{min.x,				min.y + extents.y, min.z + extents.z},
		{min.x + extents.x, min.y + extents.y, min.z}
	};

	return vertices;
}