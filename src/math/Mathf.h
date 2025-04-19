#ifndef INCL_MATHF_H
#define INCL_MATHF_H

#include <glm/glm.hpp>

constexpr float FLOAT_COMPARE_EPSILON = 1e-5;

namespace Mathf {
	template<typename T>
	inline T lerp(const T& a, const T& b, float t) {
		return a + t * (b - a);
	}

	inline float bezierCurve(float a, float b, float t, float c) {
		return (1 - t) * a * a + 2 * (1 - t) * t * c + t * t * b;
	}

	inline float quinticCurve(float t) {
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	inline bool equals(float a, float b, float epsilon = 0.0f) {
		return glm::abs(a - b) <= epsilon;
	}
}

#endif