#include "CollisionDetector.h"

#include "../../world/RayTracing.h"

void CollisionDetector::detect(std::vector<GameObject*>& objects, World& world) {
	updateTransforms(objects);
	detectO2O(objects);
	detectO2B(objects, world);
}

void CollisionDetector::updateTransforms(std::vector<GameObject*>& objects) {
	for (GameObject* obj : objects) {
		obj->updateTransform();
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

		for (float x = -1; x <= obj->model->aabb.extents.x + 1; ++x) {
			for (float z = -1; z <= obj->model->aabb.extents.z + 1; ++z) {
				for (float y = 0; y <= obj->model->aabb.extents.y + 1; ++y) {
					std::shared_ptr<Block> block = world.getBlock(obj->transform.position + glm::vec3(x, y, z));

					detectO2B(*obj, world, block);
				}
			}
		}
	
		for (const glm::vec3& vertex : obj->model->aabb.getVertices()) {
			Ray ray(vertex, obj->rigidBody.deltaPosition);
			std::shared_ptr<Block> block = RayTracing::getNearestBlock(world, ray, glm::length(obj->rigidBody.deltaPosition) + 0.1);

			detectO2B(*obj, world, block);
		}
	}
}

void CollisionDetector::detectO2B(GameObject& obj, World& world, std::shared_ptr<Block>& block) {
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