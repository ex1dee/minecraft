#include "PhysicsEngine.h"

#include "collision/CollisionDetector.h"
#include "PhysicsConstants.h"
#include "../player/Player.h"
#include "../input/Input.h"
#include "GameObject.h"

std::vector<GameObject*> PhysicsEngine::objects;
float PhysicsEngine::deltaTime;
World* PhysicsEngine::world;

void PhysicsEngine::initialize(World* world) { 
	PhysicsEngine::world = world;
}

void PhysicsEngine::finalize() { 

}

void PhysicsEngine::update(Player& player, float deltaTime) {
	PhysicsEngine::deltaTime = deltaTime;
	if (deltaTime == 0)
		return;

	glm::vec3 position = player.transform.position;
	glm::vec3 chunkPos = glm::vec3(position.x, 0, position.z);
	Chunk* chunk = world->getChunk(chunkPos);

	if (chunk == nullptr || !chunk->isLoaded())
		return;

	cullObjects();

	for (GameObject* object : objects) {
		prepare(object);
	}

	CollisionDetector::detect(objects, world);

	for (GameObject* object : objects) {
		updatePosition(object);
	}
}

void PhysicsEngine::cullObjects() {
	objects.erase(std::remove(objects.begin(), objects.end(), nullptr), objects.end());
}

void PhysicsEngine::prepare(GameObject* object) {
	RigidBody* rb = &object->rigidBody;

	addForces(object);

	rb->acceleration = rb->force / rb->mass;
	rb->newVelocity = rb->velocity + rb->acceleration * deltaTime;
	rb->deltaPosition = rb->newVelocity * deltaTime;

	rb->force = glm::vec3(0);
}

void PhysicsEngine::addForces(GameObject* object) {
	RigidBody* rb = &object->rigidBody;

	if (rb->physicsType == PhysicsType::STATIC) {
		rb->force = glm::vec3(0);
	} else {
		rb->force += GRAVITY;

		Liquid* liquid = object->getLiquidAtObject();

		if (liquid != nullptr) {
			rb->force += ARHIMEDE;
			rb->force.y -= glm::min(0.0f, rb->velocity.y) * liquid->getViscosity();
		}
	}
}

void PhysicsEngine::updatePosition(GameObject* object) {
	RigidBody* rb = &object->rigidBody;

	object->transform.position += rb->deltaPosition;
	rb->velocity = rb->newVelocity;
}

void PhysicsEngine::addObject(GameObject* object) {
	objects.push_back(object);
}