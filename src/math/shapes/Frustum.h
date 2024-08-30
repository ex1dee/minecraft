#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <array>

#include "Plane.h"
#include "AABB.h"

class Frustum {
public:
	std::array<Plane, 6> planes;

	Frustum() = default;

	void update(const glm::mat4& projView);
	bool isAABBInFrustum(const AABB& aabb) const;
};

#endif