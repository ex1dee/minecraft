#ifndef BLOCKCOLLIDERS_H
#define BLOCKCOLLIDERS_H

#include "../../physics/collider/BoxCollider.h"
#include "BlockColliderType.h"

class BlockColliders {
public:
	static std::vector<BoxCollider*> get(BlockColliderType type) {
		std::vector<BoxCollider*> colliders;

		if (type == FULL_SIZE) {
			colliders.push_back(new BoxCollider(glm::vec3(1)));
		}

		return colliders;
	}
};

#endif