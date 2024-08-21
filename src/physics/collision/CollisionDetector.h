#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "../../world/World.h"
#include "BoxBoxCollision.h"
#include "../GameObject.h"

class CollisionDetector {
	static void detect(GameObject& obj1, GameObject& obj2);

	static void applyTransforms(std::vector<GameObject*>& objects);
	static void detectO2O(std::vector<GameObject*>& objects);
	static void detectO2B(GameObject& obj, World& world, std::shared_ptr<Block>& block);
	static void detectO2B(std::vector<GameObject*>& objects, World& world);
public:
	static void detect(std::vector<GameObject*>& objects, World& world);
};

#endif