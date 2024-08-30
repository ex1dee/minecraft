#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <vector>

#include "../../math/shapes/Rect.h"
#include "Collider.h"

class BoxCollider : public Collider {
	std::vector<glm::vec3> vertices;
	glm::vec3 extents;

	void calcVertices();
public:
	std::vector<glm::vec3> globalVertices;

	BoxCollider(const glm::vec3& extents, const Transform& transform = Transform());
	
	const glm::vec3& getExtents() { return extents; }

	std::vector<Rect> getRectangles(const Transform& transform);
	void updateTransform(const Transform& transform) override;
};

#endif