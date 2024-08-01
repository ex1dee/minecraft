#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>

#include "../../math/Transform.h"

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

	virtual void applyTransform(Transform& transform) = 0;

	ColliderType getType() { return type; }
	glm::vec3 getPosition() { return position; }
	glm::vec3 getRotation() { return rotation; }
	glm::vec3 getScale() { return rotation; }
};

enum ColliderType {
	BOX
};

#endif