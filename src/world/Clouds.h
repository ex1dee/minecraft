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

	std::unique_ptr<NoiseMap> noiseMap;
	std::shared_ptr<Sprite> sprite;
	std::shared_ptr<Player> player;
	PerlinNoise2D noise;
	uint32_t seed;
	World* world;

	void setup();
	void updateNoise();
	void updateTexture();
	void updateNoiseCycle();
	void updatePosition(float deltaTime);
public:
	Clouds(const Clouds& clouds) = default;
	Clouds(uint32_t seed, std::shared_ptr<Player>& player, World& world);
	~Clouds();

	std::shared_ptr<Sprite> getSprite() const { return sprite; }

	void update(float deltaTime);
};

#endif