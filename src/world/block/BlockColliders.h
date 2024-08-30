#ifndef BLOCKCOLLIDERS_H
#define BLOCKCOLLIDERS_H

#include "../../physics/collider/BoxCollider.h"
#include "BlockColliderType.h"

class BlockColliders {
public:
	static std::vector<std::unique_ptr<BoxCollider>> get(BlockColliderType type) {
		std::vector<std::unique_ptr<BoxCollider>> colliders;

		if (type == FULL_SIZE) {
			colliders.push_back(std::make_unique<BoxCollider>(glm::vec3(1.0f)));
		}

		return colliders;
	}
};

#endif