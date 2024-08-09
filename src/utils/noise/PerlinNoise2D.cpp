#include "PerlinNoise2D.h"

#include "../../math/Mathf.h"

void PerlinNoise2D::setup(uint8_t seed) {
	RandomGenerator randomGen(seed);

	generatePermutations(randomGen);
}

void PerlinNoise2D::generatePermutations(RandomGenerator& randomGen) {
	permutations.resize(PERLIN_NOISE_SIZE);

	for (int i = 0; i < PERLIN_NOISE_SIZE; ++i) {
		permutations[i] = randomGen.generateByte() & 3;
	}
}

float PerlinNoise2D::noise(float x, float y, int octaves, float persistance) {
	float amplitude = 1.0f;
	float maxAmplitude = 0.0f;
	float frequence = 1.0f;
	float result = 0.0f;

	for (int i = 0; i < octaves; ++i) {
		result += noise(x * frequence, y * frequence) * amplitude;

		maxAmplitude += amplitude;
		amplitude *= persistance;
		frequence *= 2;
	}

	return result / maxAmplitude;
}

float PerlinNoise2D::noise(float x, float y) {
	int left = (int)floor(x);
	int top = (int)floor(y);

	float pointX = x - left;
	float pointY = y - top;

	glm::vec2 topLeftGradient = getGradient(left, top);
	glm::vec2 topRightGradient = getGradient(left + 1, top);
	glm::vec2 bottomLeftGradient = getGradient(left, top + 1);
	glm::vec2 bottomRightGradient = getGradient(left + 1, top + 1);

	glm::vec2 distanceToTopLeft(pointX, pointY);
	glm::vec2 distanceToTopRight(pointX - 1, pointY);
	glm::vec2 distanceToBottomLeft(pointX, pointY - 1);
	glm::vec2 distanceToBottomRight(pointX - 1, pointY - 1);

	float topLeftDot = glm::dot(distanceToTopLeft, topLeftGradient);
	float topRightDot = glm::dot(distanceToTopRight, topRightGradient);
	float bottomLeftDot = glm::dot(distanceToBottomLeft, bottomLeftGradient);
	float bottomRightDot = glm::dot(distanceToBottomRight, bottomRightGradient);

	pointX = Mathf::quinticCurve(pointX);
	pointY = Mathf::quinticCurve(pointY);

	float topLerp = Mathf::lerp(topLeftDot, topRightDot, pointX);
	float bottomLerp = Mathf::lerp(bottomLeftDot, bottomRightDot, pointX);

	return Mathf::lerp(topLerp, bottomLerp, pointY);
}

glm::vec2 PerlinNoise2D::getGradient(int x, int y) {
	int i = (int)(((x * 1836311903) ^ (y * 2971215073) + 4807526976) & (PERLIN_NOISE_SIZE - 1));

	const glm::vec2 gradients[4] = {
		glm::vec2(1, 0),
		glm::vec2(-1, 0),
		glm::vec2(0, 1),
		glm::vec2(0,-1)
	};

	return gradients[permutations[i]];
}