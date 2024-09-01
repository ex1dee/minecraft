#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>

class Player;
class World;
class GameObject; 

class PhysicsEngine {
	static std::vector<GameObject*> objects;
	static World* world;
	static float deltaTime;

	static void prepare(GameObject& object);
	static void addForces(GameObject& object);
	static void updatePosition(GameObject& object);
public:
	static void initialize(World& world);

	static void update(float deltaTime);
	static void addObject(GameObject& object);
	static void removeObject(const GameObject& object);
};

#endif