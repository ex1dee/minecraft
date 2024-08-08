#ifndef INCL_MATHF_H
#define INCL_MATHF_H

#include <glm/glm.hpp>

namespace Mathf {
	inline float lerp(float a, float b, float t) {
		t = glm::clamp(t, 0.0f, 1.0f);
		
		return a + t * (b - a);
	}

	inline float bezierCurve(float a, float b, float t, float c) {
		t = glm::clamp(t, 0.0f, 1.0f);

		return (1 - t) * a * a + 2 * (1 - t) * t * c + t * t * b;
	}

	inline bool equals(float a, float b, float epsilon) {
		return glm::abs(a - b) <= epsilon;
	}
}

#endif