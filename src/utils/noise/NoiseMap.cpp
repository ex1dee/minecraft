#include "NoiseMap.h"

NoiseMap::NoiseMap(int width, int height)
	: map(width, height, 1) {

}

NoiseMap::~NoiseMap() {
	map.free();
}

void NoiseMap::apply(const SetNoiseFunc& func) {
	for (int x = 0; x < map.width; ++x) {
		for (int y = 0; y < map.height; ++y) {
			int index = getIndex(x, y);
			map.data[index] = func(x, y);
		}
	}
}

void NoiseMap::apply(const ChangeNoiseFunc& func) {
	for (int x = 0; x < map.width; ++x) {
		for (int y = 0; y < map.height; ++y) {
			int index = getIndex(x, y);
			map.data[index] = func(map.data[index]);
		}
	}
}

void NoiseMap::reset() {
	for (int i = 0; i < map.width * map.height; ++i) {
		map.data[i] = 0;
	}
}