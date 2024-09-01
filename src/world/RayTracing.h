#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "../math/shapes/Ray.h"
#include "World.h"

class RayTracing {
	static glm::vec3 getBundle(const Ray& ray, float maxDistance);
public:
	static std::shared_ptr<Block> getNearestBlock(World& world, const Ray& ray, float maxDistance);
	static std::vector<std::shared_ptr<Block>> getBlocks(World& world, const Ray& ray, float maxDistance);
};

#endif