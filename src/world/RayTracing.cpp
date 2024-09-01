#include "RayTracing.h"

constexpr float RAYTRACING_BUNDLE_LEN = 0.1f;

std::shared_ptr<Block> RayTracing::getNearestBlock(World& world, const Ray& ray, float maxDistance) {
	glm::vec3 bundle = normalize(ray.direction) * glm::min(maxDistance * RAYTRACING_BUNDLE_LEN, RAYTRACING_BUNDLE_LEN);

	if (glm::length(bundle) == 0)
		return nullptr;

	for (glm::vec3 currentPos = ray.start; glm::length(currentPos - ray.start) <= maxDistance; currentPos += bundle) {
		if (currentPos.y < 0 || currentPos.y >= CHUNK_H)
			continue;

		std::shared_ptr<Block> block = world.getBlock(currentPos);

		if (block != nullptr && block->isCollidable()) {
			return block;
		}
	}

	return nullptr;
}

std::vector<std::shared_ptr<Block>> RayTracing::getBlocks(World& world, const Ray& ray, float maxDistance) {
	std::vector<std::shared_ptr<Block>> blocks;
	glm::vec3 bundle = getBundle(ray, maxDistance);

	if (glm::length(bundle) == 0)
		return blocks;
	
	for (glm::vec3 currentPos = ray.start; glm::length(currentPos - ray.start) <= maxDistance; currentPos += bundle) {
		if (currentPos.y < 0 || currentPos.y >= CHUNK_H)
			continue;

		std::shared_ptr<Block> block = world.getBlock(currentPos);

		if (block != nullptr && block->isCollidable()) {
			blocks.push_back(block);

			currentPos += 1.0f - bundle;
		}
	}

	return blocks;
}

glm::vec3 RayTracing::getBundle(const Ray& ray, float maxDistance) {
	return glm::normalize(ray.direction)* glm::min(maxDistance * RAYTRACING_BUNDLE_LEN, RAYTRACING_BUNDLE_LEN);
}