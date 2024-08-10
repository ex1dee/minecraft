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

	static void cullObjects();
	static void prepare(GameObject* object);
	static void addForces(GameObject* object);
	static void updatePosition(GameObject* object);
public:
	static void initialize(World* world);
	static void finalize();

	static void update(Player& player, float deltaTime);
	static void addObject(GameObject* object);
};

#endif