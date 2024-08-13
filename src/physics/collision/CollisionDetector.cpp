#include "CollisionDetector.h"

#include "../../world/RayTracing.h"

void CollisionDetector::detect(std::vector<GameObject*>& objects, World& world) {
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
			GameObject& obj1 = *objects[i];
			GameObject& obj2 = *objects[j];

			detect(obj1, obj2);
		}
	}
}

void CollisionDetector::detectO2B(std::vector<GameObject*>& objects, World& world) {
	for (GameObject* obj : objects) {
		if (obj->rigidBody.physicsType == PhysicsType::STATIC)
			continue;

		glm::vec3 newPosition = obj->transform.position + 0.5f * glm::normalize(obj->rigidBody.deltaPosition);
		Chunk* chunk = world.getChunk(glm::vec3(newPosition.x, 0, newPosition.z));

		if (chunk == nullptr || !chunk->isLoaded())
			continue;

		for (float x = -1; x <= obj->model->aabb.extents.x + 1; ++x) {
			for (float y = -1; y <= obj->model->aabb.extents.y + 1; ++y) {
				for (float z = -1; z <= obj->model->aabb.extents.z + 1; ++z) {
					glm::vec3 blockPosition = newPosition + glm::vec3(x, y, z);
					Block* block = world.getBlock(glm::floor(blockPosition));

					detectO2B(*obj, world, block);
				}
			}
		}
	}
}

void CollisionDetector::detectO2B(GameObject& obj, World& world, Block* block) {
	if (block == nullptr)
		return;

	BoxBoxCollision::detect(obj, *block);
}

void CollisionDetector::detect(GameObject& obj1, GameObject& obj2) {
	ColliderType type1 = obj1.collider->getType();
	ColliderType type2 = obj2.collider->getType();
	
	if (type1 == ColliderType::BOX && type2 == ColliderType::BOX) {
		BoxBoxCollision::detect(obj1, obj2);
	}
}