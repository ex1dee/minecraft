#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>
#include <mutex>

class Timer {
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
	~Timer();
	
	float getSecPerTick() { return (float)secPerTick; }

	void start(double secPerTick, std::atomic<bool>* isRunning);
	bool isTickElapsed();
};

#endif