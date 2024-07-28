#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <array>

#include "AABB.h"
#include "Plane.h"

struct Frustum {
	std::array<Plane*, 6> planes;

	Frustum();
	~Frustum();

	void update(const glm::mat4& pv);
	bool isAABBInFrustum(const AABB& aabb);
};

#endif