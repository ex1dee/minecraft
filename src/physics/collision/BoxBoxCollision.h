#ifndef BOXBOXCOLLISION_H
#define BOXBOXCOLLISION_H

#include "../collider/BoxCollider.h"
#include "../../world/block/Block.h"
#include "../GameObject.h"
#include "CollisionHandler.h"
#include "Collision.h"

#define PROJECTION_MIN_INDEX 0
#define PROJECTION_MAX_INDEX 1

class BoxBoxCollision {
	static std::vector<glm::vec3> calcBoxSepAxes(BoxCollider* box1, BoxCollider* box2);
	static glm::vec2 projAxis(std::vector<glm::vec3>& vertices, const glm::vec3& axis);
	static float proj(const glm::vec3& a, const glm::vec3& b);

	static Collision detect(BoxCollider* b1, BoxCollider* b2);
public:
	static void detect(GameObject* obj1, GameObject* obj2);
	static void detect(GameObject* obj, Block* block);
};

#endif