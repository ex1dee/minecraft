#ifndef ENTITY_H
#define ENTITY_H

#include "../physics/GameObject.h"

class Entity : public GameObject {
public:
	Entity() 
		: GameObject(true, false, 1.0f) {
		rigidBody.addForce(GRAVITY);
	}
};

#endif