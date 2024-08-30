#ifndef BOXBOXCOLLISION_H
#define BOXBOXCOLLISION_H

#include "../collider/BoxCollider.h"
#include "../../world/block/Block.h"
#include "../GameObject.h"
#include "CollisionHandler.h"
#include "Collision.h"

class BoxBoxCollision {
	static std::vector<glm::vec3> calcBoxSepAxes(const BoxCollider& box1, const BoxCollider& box2);
	static glm::vec2 projAxis(const std::vector<glm::vec3>& vertices, const glm::vec3& axis);
	static float proj(const glm::vec3& a, const glm::vec3& b);

public:
	static void detect(GameObject& obj1, GameObject& obj2);
	static void detect(GameObject& obj, const Block& block);
	static Collision detect(const BoxCollider& b1, const BoxCollider& b2);
};

#endif