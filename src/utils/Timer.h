#ifndef TIMER_H
#define TIMER_H

class Timer {
protected:
	float lastTime;
	float deltaTime;
	float resetTime;
	float currentTime;
public:
	Timer();

	void reset();
	float getDeltaTime();
};

#endif