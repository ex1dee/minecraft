#ifndef COLLISION_HANDLER
#define COLLISION_HANDLER

#include "../../world/block/Block.h"
#include "../GameObject.h"
#include "Collision.h"

class CollisionHandler {
	static glm::vec3 getProjected(const glm::vec3& v, const Collision& collision);
public:
	static void handle(const Collision& collision, GameObject& obj, const Block& block);
	static void handle(const Collision& collision, GameObject& obj1, GameObject& obj2);
};

#endif