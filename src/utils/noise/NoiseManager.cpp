#include "NoiseManager.h"

#include "../../math/Mathf.h"

float NoiseManager::remap(float noise, float old_min, float old_max, float new_min, float new_max) {
	return (noise - old_min) / (old_max - old_min) * (new_max - new_min) + new_min;
}

float NoiseManager::select(float noise, float falloffNoise, float sampleNoise, float maxNoiseToFalloff, float minNoiseToSelect) {
	if (sampleNoise >= minNoiseToSelect) {
		return noise;
	} else if (sampleNoise <= maxNoiseToFalloff) {
		return falloffNoise;
	} else {
		return Mathf::lerp(noise, falloffNoise, 1.0f / ((minNoiseToSelect - maxNoiseToFalloff) / (minNoiseToSelect - sampleNoise)));
	}
}