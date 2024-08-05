#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>

class Triangle {
public:
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;

	Triangle() {}
	Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
		: a(a), b(b), c(c) {}

	float getArea() const {
		return 0.5f * glm::length(glm::cross(b - a, c - a));
	}
};

#endif