#include "Timer.h"

#include <GLFW/glfw3.h>

Timer::~Timer() {
	thread.join();
}

void Timer::start(double secPerTick, std::atomic<bool>* isRunning) {
	*isRunning = true;

	this->secPerTick = secPerTick;
	this->isRunning = isRunning;
	this->lastTime = 0;

	thread = std::thread([&]() { update(); });
}

void Timer::update() {
	while (isRunning) {
		std::this_thread::sleep_for(std::chrono::microseconds(100));

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		if (!tickElapsed) {
			tickLag += deltaTime;

			if (tickLag >= secPerTick) {
				tickElapsed = true;
				tickLag = 0;
			}
		}
	}
}

bool Timer::isTickElapsed() {
	if (tickElapsed) {
		tickElapsed = false;

		return true;
	}

	return false;
}