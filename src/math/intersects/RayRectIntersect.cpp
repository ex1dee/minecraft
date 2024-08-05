#include "RayRectIntersect.h"

#include "../shapes/Plane.h"

Intersect1P RayRectIntersect::intersect(const Ray& ray, const Rect& rect) {
	Plane plane(rect);

	float x0 = ray.start.x;
	float y0 = ray.start.y;
	float z0 = ray.start.z;

	float dx = ray.direction.x;
	float dy = ray.direction.y;
	float dz = ray.direction.z;

	float A = plane.normal.x;
	float B = plane.normal.y;
	float C = plane.normal.z;
	float D = plane.distance;

	float t = -(A * x0 + B * y0 + C * z0 + D) / (A * dx + B * dy + C * dz);
	glm::vec3 point = ray.start + glm::normalize(ray.direction) * t;

	Intersect1P intersect;

	if (t >= 0 && rect.isPointInside(point)) {
		intersect.intersected = true;
		intersect.point = point;
	} else {
		intersect.intersected = false;
	}

	return intersect;
}