#include "NoiseMap.h"

NoiseMap::NoiseMap(int width, int height)
	: map(GL_FLOAT, width, height, 1) {
	map.allocData();
}

NoiseMap::~NoiseMap() {
	map.free();
}

void NoiseMap::apply(const SetNoiseFunc& func) {
	for (int x = 0; x < map.width; ++x) {
		for (int y = 0; y < map.height; ++y) {
			int index = getIndex(x, y);
			map[index] = func(x, y);
		}
	}
}

void NoiseMap::apply(const ChangeNoiseFunc& func) {
	for (int x = 0; x < map.width; ++x) {
		for (int y = 0; y < map.height; ++y) {
			int index = getIndex(x, y);
			map[index] = func(map[index]);
		}
	}
}

void NoiseMap::reset() {
	for (int i = 0; i < map.width * map.height; ++i) {
		map[i] = 0;
	}
}