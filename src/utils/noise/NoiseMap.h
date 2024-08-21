#ifndef NOISEMAP_H
#define NOISEMAP_H

#include <functional>

#include "../../textures/CustomImage.h"

typedef std::function<float(int, int)> SetNoiseFunc;
typedef std::function<float(float)> ChangeNoiseFunc;

class NoiseMap {
	CustomImage<float> map;

	int getIndex(int x, int y) { return y * map.width + x; }
public:
	NoiseMap(int width, int height);
	~NoiseMap();

	const CustomImage<float>& getMap() { return map; }
	float get(int x, int y) { return map[getIndex(x, y)]; }

	void reset();
	void apply(const SetNoiseFunc& func);
	void apply(const ChangeNoiseFunc& func);
};

#endif