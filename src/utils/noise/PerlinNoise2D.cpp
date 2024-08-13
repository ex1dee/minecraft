#include "PerlinNoise2D.h"

#include "../../math/Mathf.h"
#include "NoiseManager.h"

constexpr int PERLIN_NOISE_SIZE = 1024;

void PerlinNoise2D::setup(uint32_t seed, const NoiseConfig& config) {
	this->config = config;

	RandomGenerator randomGen(seed);
	generatePermutations(randomGen);
}

void PerlinNoise2D::generatePermutations(RandomGenerator& randomGen) {
	permutations.resize(PERLIN_NOISE_SIZE);

	for (int i = 0; i < PERLIN_NOISE_SIZE; ++i) {
		permutations[i] = randomGen.generateByte() & 3;
	}
}

float PerlinNoise2D::FBM(float x, float y, int octaves) {
	float frequency = config.frequency;
	float amplitude = 1.0f;
	float maxAmplitude = 0.0f;
	float result = 0.0f;

	for (int i = 0; i < octaves; ++i) {
		result += noise(x * frequency, y * frequency) * amplitude;

		maxAmplitude += amplitude;
		amplitude *= config.persistance;
		frequency *= config.lacunarity;
	}

	return pow(result / maxAmplitude, config.redistribution);
}

float PerlinNoise2D::ridgeFBM(float x, float y, int octaves) {
	float frequency = config.frequency;
	float maxAmplitude = 0.0f;
	float amplitude = 1.0f;
	float result = 0.0f;

	for (int i = 0; i < octaves; ++i) {
		float d = 1.0f;

		if (result)
			d = result;

		result += ridgeNoise(x * frequency, y * frequency) * amplitude * d;

		maxAmplitude += amplitude;
		amplitude *= config.persistance;
		frequency *= config.lacunarity;
	}

	return pow(result / maxAmplitude, config.redistribution);
}

float PerlinNoise2D::ridgeNoise(float x, float y) {
	return 2.0f * (0.5f - glm::abs(0.5f - noise(x, y)));
}

float PerlinNoise2D::noise(float x, float y) {
	glm::vec2 point(x, y);

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

	float result = NoiseManager::remap(
		Mathf::lerp(topLerp, bottomLerp, pointY),
		-1.0f, 1.0f,
		config.noise_min, config.noise_max
	);

	return result;
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
