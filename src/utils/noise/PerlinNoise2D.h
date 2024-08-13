#ifndef PERLINNOISE2D_H
#define PERLINNOISE2D_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <glm/glm.hpp>
#include <vector>

#include "../random/Random.h"
#include "NoiseConfig.h"

class PerlinNoise2D {
	std::vector<uint8_t> permutations;
	NoiseConfig config;

	glm::vec2 getGradient(int x, int y);
	void generatePermutations(RandomGenerator& randomGen);
public:
	void setup(uint32_t seed, const NoiseConfig& config);

	float noise(float x, float y);
	float FBM(float x, float y, int octaves);

	float ridgeNoise(float x, float y);
	float ridgeFBM(float x, float y, int octaves);
};

#endif