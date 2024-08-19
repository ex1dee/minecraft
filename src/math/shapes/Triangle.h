#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../geometry/Transform.h"

class Triangle {
public:
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;

	Triangle() = default;
	Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
		: a(a), b(b), c(c) {}

	virtual float getArea() const {
		return 0.5f * glm::length(glm::cross(b - a, c - a));
	}

	virtual void applyTransform(const Transform& transform) {
		glm::mat4 model = transform.calcModel();

		a = glm::vec3(model * glm::vec4(a, 1));
		b = glm::vec3(model * glm::vec4(b, 1));
		c = glm::vec3(model * glm::vec4(c, 1));
	}
};

#endif