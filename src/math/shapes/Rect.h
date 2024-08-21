#ifndef RECT_H
#define RECT_H

#include "../Mathf.h"
#include "Triangle.h"

constexpr float POINT_INSIDE_EPSILON = 0.03f;

class Rect : public Triangle {
public:
	glm::vec3 d;

	Rect() = default;
	Rect(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d)
		: Triangle(a, b, c), d(d) {
		
	}

	Rect(Rect&& other) noexcept {
		a = std::move(other.a);
		b = std::move(other.b);
		c = std::move(other.c);
		d = std::move(other.d);
	}

	bool isPointInside(const glm::vec3& p) const {
		float s_apb = Triangle(a, p, b).getArea();
		float s_apd = Triangle(a, p, d).getArea();
		float s_bpc = Triangle(b, p, c).getArea();
		float s_dpc = Triangle(d, p, c).getArea();

		return Mathf::equals(getArea(), s_apb + s_apd + s_bpc + s_dpc, POINT_INSIDE_EPSILON);
	}

	float getArea() const override {
		return Triangle::getArea() * 2.0f;
	}

	void applyTransform(const Transform& transform) override {
		glm::mat4 model = transform.calcModel();

		a = glm::vec3(model * glm::vec4(a, 1));
		b = glm::vec3(model * glm::vec4(b, 1));
		c = glm::vec3(model * glm::vec4(c, 1));
		d = glm::vec3(model * glm::vec4(d, 1));
	}
};

#endif