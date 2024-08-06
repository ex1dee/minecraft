#include "RayTracing.h"

Block* RayTracing::getNearestBlock(World* world, const Ray& ray, float maxDistance) {
	glm::vec3 bundle = normalize(ray.direction) * RAYTRACING_BUNDLE_LEN;

	for (glm::vec3 currentPos = ray.start; glm::length(currentPos - ray.start) <= maxDistance; currentPos += bundle) {
		Block* block = world->getBlock(currentPos);

		if (block->type->colliders.size()) {
			return block;
		}
	}

	return nullptr;
}