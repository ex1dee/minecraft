#include "RayBoxIntersect.h"

#include "RayRectIntersect.h"

IntersectList RayBoxIntersect::intersect(const Ray& ray, BoxCollider* collider, const Transform& boxTransform) {
	IntersectList intersects;

	for (Rect& rect : collider->getRectangles(boxTransform)) {
		if (intersects.isComplete(2))
			break;

		Intersect1P intersect = RayRectIntersect::intersect(ray, rect);

		if (intersect.intersected)
			intersects.list.push_back(intersect.point);
	}

	return intersects;
}