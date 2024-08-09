#include "RayTracing.h"

Block* RayTracing::getNearestBlock(World* world, const Ray& ray, float maxDistance) {
	glm::vec3 bundle = normalize(ray.direction) * glm::min(maxDistance * RAYTRACING_BUNDLE_LEN, RAYTRACING_BUNDLE_LEN);

	if (glm::length(bundle) == 0)
		return nullptr;

	for (glm::vec3 currentPos = ray.start; glm::length(currentPos - ray.start) <= maxDistance; currentPos += bundle) {
		if (currentPos.y < 0 || currentPos.y >= CHUNK_H)
			continue;

		Block* block = world->getBlock(currentPos);

		if (block->isCollidable()) {
			return block;
		}
	}

	return nullptr;
}