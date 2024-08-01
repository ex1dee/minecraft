#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "../../world/World.h"
#include "BoxBoxCollision.h"
#include "../GameObject.h"

class CollisionDetector {
	static void detect(GameObject* obj1, GameObject* obj2);
	static void detect(GameObject* obj, BoxCollider* box);
public:
	static void detect(std::vector<GameObject*>& objects, World* world);
};

#endif