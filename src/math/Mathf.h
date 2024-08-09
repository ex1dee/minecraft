#ifndef INCL_MATHF_H
#define INCL_MATHF_H

#include <glm/glm.hpp>

namespace Mathf {
	inline float lerp(float a, float b, float t) {
		return a + t * (b - a);
	}

	inline float bezierCurve(float a, float b, float t, float c) {
		return (1 - t) * a * a + 2 * (1 - t) * t * c + t * t * b;
	}

	inline float quinticCurve(float t) {
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	inline bool equals(float a, float b, float epsilon) {
		return glm::abs(a - b) <= epsilon;
	}
}

#endif