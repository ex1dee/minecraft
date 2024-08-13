#ifndef NOISECONFIG_H
#define NOISECONFIG_H

class NoiseConfig {
public:
	float redistribution;
	float persistance;
	float lacunarity;
	float frequency;
	float noise_min;
	float noise_max;

	NoiseConfig(
		float noise_min = -1.0f, float noise_max = 1.0f, float redistribution = 1.0f, 
		float persistance = 0.5f, float frequency = 1.0f, float lacunarity = 2.0f)
		: noise_min(noise_min), noise_max(noise_max), redistribution(redistribution), 
		  persistance(persistance), frequency(frequency), lacunarity(lacunarity) {}
};

#endif