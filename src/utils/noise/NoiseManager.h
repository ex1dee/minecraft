#ifndef NOISEMANAGER_H
#define NOISEMANAGER_H

class NoiseManager {
public:
	static float remap(float noise, float old_min, float old_max, float new_min, float new_max);
	static float select(float noise, float falloffNoise, float sampleNoise, float maxNoiseToFalloff, float minNoiseToSelect);
};

#endif