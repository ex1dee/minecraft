#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>

class World;
class GameObject; 

class PhysicsEngine {
	static std::vector<GameObject*> objects;
	static World* world;

	static void cullObjects();
	static void prepare(GameObject* object);
	static void updatePosition(GameObject* object);
	static void update(bool updatePerTick);
	static float getDeltaTime(GameObject* object);
public:
	static void initialize(World* world);
	static void finalize();

	static void updatePerFrame();
	static void updatePerTick();
	static void addObject(GameObject* object);
};

#endif