#include "CollisionDetector.h"

void CollisionDetector::detect(std::vector<GameObject*>& objects, World* world) {
	applyTransforms(objects);
	detectO2O(objects);
	detectO2B(objects, world);
}

void CollisionDetector::applyTransforms(std::vector<GameObject*>& objects) {
	for (GameObject* obj : objects) {
		obj->applyTransform(obj->transform);
	}
}

void CollisionDetector::detectO2O(std::vector<GameObject*>& objects) {
	for (int i = 0; i < objects.size(); ++i) {
		for (int j = i + 1; j < objects.size(); ++j) {
			GameObject* obj1 = objects[i];
			GameObject* obj2 = objects[j];

			detect(obj1, obj2);
		}
	}
}

void CollisionDetector::detectO2B(std::vector<GameObject*>& objects, World* world) {
	for (GameObject* obj : objects) {
		glm::vec3 position = obj->transform.position;

		for (float x = -1; x <= obj->model->aabb.extents.x + 1; ++x) {
			for (float y = -1; y <= obj->model->aabb.extents.y + 1; ++y) {
				for (float z = -1; z <= obj->model->aabb.extents.z + 1; ++z) {
					glm::vec3 blockPosition = glm::floor(position + glm::vec3(x, y, z));
					Transform blockTrans = Transform(blockPosition);
					Block* block = world->getBlock(blockPosition);

					if (block != nullptr && block->type->isSolid) {
						for (BoxCollider* blockCollider : block->type->colliders) {
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