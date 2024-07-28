#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>

struct Plane {
	glm::vec3 normal;
	float distance;

	Plane() {}
	Plane(glm::vec3 normal, glm::vec3 point)
		: normal(glm::normalize(normal)), distance(glm::dot(normal, point)) {}

	float distanceToPoint(const glm::vec3& point) const {
		return glm::dot(normal, point) + distance;
	}
}; 

enum Planes {
	Near,
	Far,
	Left,
	Right,
	Top,
	Bottom,
};

#endif