#ifndef PERLINNOISE2D_H
#define PERLINNOISE2D_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <glm/glm.hpp>
#include <vector>

#include "../random/Random.h"

#define PERLIN_NOISE_SIZE 1024

class PerlinNoise2D {
	std::unordered_map<glm::vec2, float> noiseCache;
	std::vector<uint8_t> permutations;

	glm::vec2 getGradient(int x, int y);
	void generatePermutations(RandomGenerator& randomGen);
public:
	void setup(uint8_t seed);

	float noise(float x, float y);
	float noise(float x, float y, int octaves, float persistance = 0.5f);
};

#endif