#include "PhysicsEngine.h"

#include "collision/CollisionDetector.h"
#include "../Time.h"
#include "GameObject.h"

std::vector<GameObject*> PhysicsEngine::objects;
World* PhysicsEngine::world;

void PhysicsEngine::initialize(World* world) { 
	PhysicsEngine::world = world;
}

void PhysicsEngine::finalize() { }

void PhysicsEngine::updatePerTick() {
	update(true);
}

void PhysicsEngine::updatePerFrame() {
	update(false);
}

void PhysicsEngine::update(bool updatePerTick) {
	cullObjects();

	for (GameObject* object : objects) {
		if (updatePerTick || !object->rigidBody.updateEveryTick) {
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
	rb->newPosition = object->transform.position + rb->newVelocity * dt;
}

void PhysicsEngine::updatePosition(GameObject* object) {
	RigidBody* rb = &object->rigidBody;
	float dt = getDeltaTime(object);

	rb->velocity = rb->newVelocity;
	object->transform.position += rb->velocity * dt;
}

float PhysicsEngine::getDeltaTime(GameObject* object) {
	if (object->rigidBody.updateEveryTick)
		return Time::getTickDeltaTime();
	else
		return Time::getDeltaTime();
}

void PhysicsEngine::addObject(GameObject* object) {
	if (object->rigidBody.physics)
		objects.push_back(object);
}