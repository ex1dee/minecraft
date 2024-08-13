#ifndef RECT_H
#define RECT_H

#include "../Mathf.h"
#include "Triangle.h"

constexpr float POINT_INSIDE_EPSILON = 0.03f;

class Rect : public Triangle {
public:
	glm::vec3 d;

	Rect() {}
	Rect(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d)
		: Triangle(a, b, c), d(d) {
		
	}

	bool isPointInside(const glm::vec3& p) const {
		float s_apb = Triangle(a, p, b).getArea();
		float s_apd = Triangle(a, p, d).getArea();
		float s_bpc = Triangle(b, p, c).getArea();
		float s_dpc = Triangle(d, p, c).getArea();

		return Mathf::equals(getArea(), s_apb + s_apd + s_bpc + s_dpc, POINT_INSIDE_EPSILON);
	}

	float getArea() const {
		return Triangle::getArea() * 2.0f;
	}
};

#endif