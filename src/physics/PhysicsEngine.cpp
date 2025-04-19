#include "PhysicsEngine.h"

#include "collision/CollisionDetector.h"
#include "PhysicsConstants.h"
#include "../player/Player.h"
#include "../input/Input.h"
#include "GameObject.h"

std::vector<GameObject*> PhysicsEngine::objects;
float PhysicsEngine::deltaTime;
World* PhysicsEngine::world;

void PhysicsEngine::initialize(World& world) { 
	PhysicsEngine::world = &world;
}

void PhysicsEngine::update(float deltaTime) {
	if (deltaTime == 0)
		return;

	PhysicsEngine::deltaTime = deltaTime;

	for (GameObject* object : objects) {
		prepare(*object);
	}

	CollisionDetector::detect(objects, *world);

	for (GameObject* object : objects) {
		if (object->isAtLoadedChunk())
			updatePosition(*object);
	}
}

void PhysicsEngine::removeObject(const GameObject& object) {
	objects.erase(std::remove(objects.begin(), objects.end(), &object), objects.end());
}

void PhysicsEngine::prepare(GameObject& object) {
	RigidBody& rb = object.rigidBody;

	addForces(object);

	rb.acceleration = rb.force / rb.mass;
	rb.newVelocity = rb.velocity + rb.acceleration * deltaTime;
	rb.deltaPosition = rb.newVelocity * deltaTime;
	
	rb.force = glm::vec3(0);
}

void PhysicsEngine::addForces(GameObject& object) {
	RigidBody& rb = object.rigidBody;

	if (rb.physicsType == PhysicsType::STATIC) {
		rb.force = glm::vec3(0);
	} else {
		rb.force += rb.mass * GRAVITY;

		Liquid* liquid = object.getLiquidAtObject();

		if (liquid != nullptr) {
			rb.force += rb.mass * ARHIMEDE;
			rb.force.y -= rb.mass * glm::min(0.0f, rb.velocity.y) * liquid->getViscosity();
		}
	}
}

void PhysicsEngine::updatePosition(GameObject& object) {
	RigidBody& rb = object.rigidBody;

	object.transform.position += rb.deltaPosition;
	rb.velocity = rb.newVelocity;
}

void PhysicsEngine::addObject(GameObject& object) {
	objects.push_back(&object);
}