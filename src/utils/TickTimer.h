#ifndef TICKTIMER_H
#define TICKTIMER_H

#include "Timer.h"

#include <thread>
#include <chrono>
#include <mutex>

class TickTimer : protected Timer {
	std::atomic<bool>* isRunning;
	std::atomic<bool> tickElapsed;
	double secPerTick;
	double currentTime;
	double deltaTime;
	double lastTime;
	float tickLag;

	std::thread thread;

	void update();
public:
	~TickTimer();
	
	float getSecPerTick() { return (float)secPerTick; }

	void start(double secPerTick, std::atomic<bool>* isRunning);
	bool isTickElapsed();
};

#endif