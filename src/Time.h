#ifndef TIME_H
#define TIME_H

#define SEC_PER_TICK 0.05f

class Time {
	static float currentTime;
	static float lastTime;
	static float deltaTime;
	static float tickDeltaTime;
	static float lag;
	static bool started;
public:
	static bool needUpdate();

	static float getTickDeltaTime() { return tickDeltaTime; }
	static float getDeltaTime() { return deltaTime; }
};

#endif