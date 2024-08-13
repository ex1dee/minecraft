#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>

#include "Triangle.h"

struct Plane {
	glm::vec3 normal;
	float distance;

	Plane() = default;

	Plane(const glm::vec3& normal, const glm::vec3& point)
		: normal(glm::normalize(normal)), distance(-glm::dot(normal, point)) {}

	Plane(const Triangle& triangle) {
		glm::vec3 ab = triangle.b - triangle.a;
		glm::vec3 ac = triangle.c - triangle.a;
		
		normal = glm::cross(ab, ac);
		distance = -glm::dot(normal, triangle.a);
	}

	float distanceToPoint(const glm::vec3& point) const {
		return glm::abs(glm::dot(normal, point) + distance);
	}
}; 

#endif