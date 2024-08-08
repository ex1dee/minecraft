#include "PhysicsEngine.h"

#include "collision/CollisionDetector.h"
#include "../player/Player.h"
#include "../utils/Time.h"
#include "GameObject.h"

std::vector<GameObject*> PhysicsEngine::objects;
World* PhysicsEngine::world;

void PhysicsEngine::initialize(World* world) { 
	PhysicsEngine::world = world;
}

void PhysicsEngine::finalize() { 

}

void PhysicsEngine::updatePerLongTick(Player& player) {
	update(player, true);
}

void PhysicsEngine::updatePerTick(Player& player) {
	update(player, false);
}

void PhysicsEngine::update(Player& player, bool updatePerLongTick) {
	glm::vec3 position = player.transform.position;
	glm::vec3 chunkPos = glm::vec3(position.x, 0, position.z);

	if (!world->getChunk(chunkPos)->isLoaded())
		return;

	cullObjects();

	for (GameObject* object : objects) {
		if (updatePerLongTick || !object->rigidBody.updatePerLongTick) {
			prepare(object);
		}
	}

	CollisionDetector::detect(objects, world);

	for (GameObject* object : objects) {
		updatePosition(object);
	}
}

void PhysicsEngine::cullObjects() {
	for (auto it = objects.begin(); it != objects.end(); ++it) {
		if (*it == nullptr) {
			objects.erase(it);
		}
	}
}

void PhysicsEngine::prepare(GameObject* object) {
	RigidBody* rb = &object->rigidBody;
	float dt = getDeltaTime(object);

	rb->acceleration = rb->force / rb->mass;
	rb->newVelocity = rb->velocity + rb->acceleration * dt;
	rb->deltaPosition = rb->newVelocity * dt;
}

void PhysicsEngine::updatePosition(GameObject* object) {
	RigidBody* rb = &object->rigidBody;
	float dt = getDeltaTime(object);

	rb->velocity = rb->newVelocity;
	object->transform.position += rb->deltaPosition;
}

float PhysicsEngine::getDeltaTime(GameObject* object) {
	if (object->rigidBody.updatePerLongTick)
		return SEC_PER_PHYSICS_TICK;
	else
		return Time::getDeltaTime();
}

void PhysicsEngine::addObject(GameObject* object) {
	if (object->rigidBody.physics)
		objects.push_back(object);
}