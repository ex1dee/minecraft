#ifndef CLOUDS_H
#define CLOUDS_H

#include <thread>

#include "../textures/CustomTexture.h"
#include "../utils/noise/PerlinNoise2D.h"
#include "../utils/noise/NoiseMap.h"
#include "../render/sprite/Sprite.h"
#include "../player/Player.h"
#include "WorldConstants.h"

class World;

class Clouds {
	std::atomic<bool> isRunning = false;
	std::atomic<bool> noiseUpdated = false;
	std::atomic<bool> needUpdateNoise = false;
	std::thread updateThread;

	glm::vec3 spriteCenter;
	glm::vec3 noiseCenter;
	glm::vec3 newCenter;

	NoiseMap* noiseMap;
	PerlinNoise2D noise;
	Sprite* sprite;
	Player* player;
	World* world;
	uint32_t seed;

	void setup();
	void updateNoise();
	void updateTexture();
	void updateNoiseCycle();
	void updatePosition(float deltaTime);
public:
	Clouds(uint32_t seed, Player& player, World& world);
	~Clouds();

	Sprite* getSprite() const { return sprite; }

	void update(float deltaTime);
};

#endif