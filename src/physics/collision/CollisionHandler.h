#ifndef COLLISION_HANDLER
#define COLLISION_HANDLER

#include "../GameObject.h"
#include "Collision.h"

class CollisionHandler {
public:
	static void handle(const Collision& collision, GameObject* obj);
	static void handle(const Collision& collision, GameObject* obj1, GameObject* obj2);
};

#endif