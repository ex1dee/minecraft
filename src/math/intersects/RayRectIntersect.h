#ifndef RAYRECTINTERSECT_H
#define RAYRECTINTERSECT_H

#include "../shapes/Rect.h"
#include "../shapes/Ray.h"
#include "Intersect1P.h"

class RayRectIntersect {
public:
	static Intersect1P intersect(const Ray& ray, const Rect& rect);
};

#endif