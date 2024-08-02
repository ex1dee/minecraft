#include "CollisionDetector.h"

void CollisionDetector::detect(std::vector<GameObject*>& objects, World* world) {
	applyTransforms(objects);
	detectO2O(objects);
	detectO2B(objects, world);
}

void CollisionDetector::applyTransforms(std::vector<GameObject*>& objects) {
	for (GameObject* obj : objects) {
		Transform transform = obj->transform;
		transform.position = obj->transform.position + obj->rigidBody.deltaPosition;

		obj->applyTransform(obj->transform);
	}
}

void CollisionDetector::detectO2O(std::vector<GameObject*>& objects) {
	for (int i = 0; i < objects.size(); ++i) {
		for (int j = i + 1; j < objects.size(); ++j) {
			GameObject* obj1 = objects[i];
			GameObject* obj2 = objects[j];

			if (obj1 != obj2) {
				detect(obj1, obj2);
			}
		}
	}
}

void CollisionDetector::detectO2B(std::vector<GameObject*>& objects, World* world) {
	for (GameObject* obj : objects) {
		glm::vec3 position = obj->transform.position + obj->rigidBody.deltaPosition;;
		glm::vec3 chunkPos = glm::vec3(position.x, 0, position.z);

		if (!world->getChunk(chunkPos)->isLoaded())
			return;

		for (float x = -1; x <= obj->aabb.extents.x + 1; ++x) {
			for (float y = -1; y <= obj->aabb.extents.y + 1; ++y) {
				for (float z = -1; z <= obj->aabb.extents.z + 1; ++z) {
					glm::vec3 blockPosition = position + glm::vec3(x, y, z);
					blockPosition = glm::vec3(floor(blockPosition.x), floor(blockPosition.y), floor(blockPosition.z));
					Transform blockTrans = Transform(blockPosition);

					Block block = world->getBlock(blockPosition);

					if (block.type->isSolid) {
						for (BoxCollider* blockCollider : block.type->colliders) {
							blockCollider->applyTransform(blockTrans);

							detect(obj, blockCollider);
						}
					}
				}
			}
		}
	}
}

void CollisionDetector::detect(GameObject* obj, BoxCollider* box) {
	ColliderType type = obj->collider->getType();

	if (type == BOX) {
		BoxBoxCollision::detect(obj, box);
	}
}

void CollisionDetector::detect(GameObject* obj1, GameObject* obj2) {
	ColliderType type1 = obj1->collider->getType();
	ColliderType type2 = obj2->collider->getType();
	
	if (type1 == BOX && type2 == BOX) {
		BoxBoxCollision::detect(obj1, obj2);
	}
}