#ifndef RAYBOXINTERSECT_H
#define RAYBOXINTERSECT_H

#include "../../physics/collider/BoxCollider.h"
#include "../shapes/Ray.h"
#include "IntersectList.h"

class RayBoxIntersect {
public:
	static IntersectList intersect(const Ray& ray, BoxCollider& collider, const Transform& boxTransform);
};

#endif