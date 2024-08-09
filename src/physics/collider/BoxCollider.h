#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <vector>

#include "../../math/shapes/Rect.h"
#include "Collider.h"

class BoxCollider : public Collider {
	glm::vec3 extents = glm::vec3(0);
	std::vector<glm::vec3> vertices;

	void calcVertices();
public:
	std::vector<glm::vec3> globalVertices;

	BoxCollider(const glm::vec3& extents, const Transform& transform = Transform());
	
	const glm::vec3& getExtents() { return extents; }

	std::vector<Rect> getRectangles(const Transform& transform);
	void applyTransform(const Transform& transform) override;
};

#endif