#ifndef TIME_H
#define TIME_H

#define SEC_PER_TICK 0.05f
#define SEC_PER_PHYSICS_TICK 0.001f

class Time {
	static float currentTime;
	static float lastTime;
	static float deltaTime;
	static float tickLag;
	static float physicsTickLag;
	static bool started;
	static bool tickElapsed;
	static bool physicsTickElapsed;
public:
	static void update();

	static bool isTickElapsed() { return tickElapsed; }
	static bool isPhysicsTickElapsed() { return physicsTickElapsed; }
	static float getDeltaTime() { return deltaTime; }
};

#endif