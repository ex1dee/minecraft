#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>

#include "../../math/geometry/Transform.h"

enum class ColliderType;

class Collider : protected Transform {
private:
	ColliderType type;
public:
	Collider() = default;
	Collider(ColliderType type, const Transform& transform)
		: type(type) {

		position = transform.position;
		rotation = transform.rotation;
		scale = transform.scale;
	}

	virtual ~Collider() = default;

	ColliderType getType() { return type; }
	glm::vec3 getPosition() { return position; }
	glm::vec3 getRotation() { return rotation; }
	glm::vec3 getScale() { return rotation; }

	virtual void updateTransform(const Transform& transform) = 0;
};

enum class ColliderType {
	BOX
};

#endif