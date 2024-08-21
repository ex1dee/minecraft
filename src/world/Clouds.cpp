#include "Clouds.h"

#include "../utils/noise/NoiseManager.h"
#include "../config/Config.h"
#include "WorldConstants.h"

constexpr float
CLOUDS_NOISE_MAP_SIZE = 256.0f,
CLOUDS_SCALE = 8.0f,
CLOUDS_VISIBLE_DIST = 512.f,
CLOUDS_CHANGE_CENTER_DIST = (CLOUDS_NOISE_MAP_SIZE * CLOUDS_SCALE * 0.5f - CLOUDS_VISIBLE_DIST),
CLOUDS_NOISE_MIN = -1.0f,
CLOUDS_NOISE_MAX = 1.0f,
CLOUDS_FREQUENCY = 0.1f;

constexpr int
CLOUDS_UPDATE_INTERVAL_MS = 50;

constexpr glm::vec3
CLOUDS_MOVING_VELOCITY = glm::vec3(0.0f, 0.0f, 25.0f);

const NoiseConfig 
CLOUDS_NOISE_CONFIG(CLOUDS_NOISE_MIN, CLOUDS_NOISE_MAX, 1.0f, 0.1f, CLOUDS_FREQUENCY, 0.1f);

Clouds::Clouds(uint32_t seed, std::shared_ptr<Player>& player, World& world)
	: seed(seed), player(player), world(&world) {
	setup();

	isRunning = true;
	updateThread = std::thread(&Clouds::updateNoiseCycle, this);
}

Clouds::~Clouds() {
	isRunning = false;
	updateThread.join();

	sprite->resetTexture();
}

void Clouds::setup() {
	noiseMap = std::make_unique<NoiseMap>(CLOUDS_NOISE_MAP_SIZE, CLOUDS_NOISE_MAP_SIZE);
	noise.setup(seed, CLOUDS_NOISE_CONFIG);

	sprite = std::make_shared<Sprite>();
	sprite->transform.rotation = glm::vec3(90, 0, 0);
	sprite->transform.scale = glm::vec3(CLOUDS_SCALE, CLOUDS_SCALE, 1);
	sprite->texture.useAtlas = false;

	spriteCenter = player->transform.position;
	noiseCenter = glm::vec3(0);

	updatePosition(0);
	updateNoise();
	updateTexture();

	sprite->setup();
}

void Clouds::updatePosition(float deltaTime) {
	if (!needUpdateNoise) {
		spriteCenter += CLOUDS_MOVING_VELOCITY * deltaTime;
		newCenter = glm::vec3(player->transform.position.x, 0, player->transform.position.z);

		if (glm::distance(newCenter, spriteCenter) >= CLOUDS_CHANGE_CENTER_DIST) {
			needUpdateNoise = true;
		}

		sprite->transform.position = glm::vec3(spriteCenter.x, (float)CHUNK_H, spriteCenter.z);
	}
}

void Clouds::updateNoiseCycle() {
	while (isRunning) {
		std::this_thread::sleep_for(std::chrono::milliseconds(CLOUDS_UPDATE_INTERVAL_MS));

		if (needUpdateNoise) {
			noiseCenter += spriteCenter - newCenter;
			spriteCenter = newCenter;

			updateNoise();

			needUpdateNoise = false;
		}
	}
}

void Clouds::updateNoise() {
	glm::vec3 noisePoint = noiseCenter / CLOUDS_SCALE - CLOUDS_NOISE_MAP_SIZE * 0.5f;

	noiseMap->apply([&](int mapX, int mapY) {
		return NoiseManager::remap(
			glm::clamp(
				noise.ridgeFBM(noisePoint.x - mapX, noisePoint.z - mapY, 5),
				-1.0f, 1.0f
			),
			-1.0f, 1.0f,
			0.0f, 1.0f
		);
	});

	noiseUpdated = true;
}

void Clouds::update(float deltaTime) {
	updatePosition(deltaTime);
	updateTexture();
}

void Clouds::updateTexture() {
	if (noiseUpdated) {
		sprite->resetTexture();
		sprite->texture.data = std::make_shared<CustomTexture<float>>(noiseMap->getMap(), GL_MIRRORED_REPEAT, GL_LINEAR);

		noiseUpdated = false;
	}
}