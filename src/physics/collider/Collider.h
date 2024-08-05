#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>

#include "../../math/geometry/Transform.h"

enum ColliderType;

class Collider : protected Transform {
private:
	ColliderType type;
public:
	Collider() {}

	Collider(ColliderType type, const Transform& transform)
		: type(type) {

		position = transform.position;
		rotation = transform.rotation;
		scale = transform.scale;
	}

	ColliderType getType() { return type; }
	glm::vec3 getPosition() { return position; }
	glm::vec3 getRotation() { return rotation; }
	glm::vec3 getScale() { return rotation; }

	virtual void applyTransform(const Transform& transform) = 0;
};

enum ColliderType {
	BOX
};

#endif