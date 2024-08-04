#ifndef MATH_H
#define MATH_H

#include <glm/glm.hpp>

float lerp(float a, float b, float t) {
	t = glm::clamp(t, 0.0f, 1.0f);

	return a + t * (b - a);
}

float bezcurve(float a, float b, float t) {
	t = glm::clamp(t, 0.0f, 1.0f);
	
	return (1 - t) * a * a + 2 * (1 - t) * t * a + t * t * b;
}

#endif