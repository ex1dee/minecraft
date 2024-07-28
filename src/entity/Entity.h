#ifndef ENTITY_H
#define ENTITY_H

#include "../math/Transform.h"

class Entity {
protected:

public:
	Transform* transform;

	Entity() {
		transform = new Transform();
	}
	~Entity() {
		delete transform;
	}
};

#endif