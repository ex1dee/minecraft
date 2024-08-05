#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "../math/shapes/Ray.h"
#include "World.h"

#define RAYTRACING_BUNDLE_LEN 0.1f

class RayTracing {
public:
	static Block* getNearestBlock(World* world, const Ray& ray, float maxDistance);
};

#endif