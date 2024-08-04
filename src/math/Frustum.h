#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <array>

#include "AABB.h"
#include "Plane.h"

class Frustum {
	void normalizePlanes();
public:
	std::array<Plane*, 6> planes;

	Frustum();
	~Frustum();

	void update(const glm::mat4& projView);
	bool isAABBInFrustum(const AABB& aabb);
};

#endif