#include "TickTimer.h"

#include <GLFW/glfw3.h>

TickTimer::~TickTimer() {
	thread.join();
}

void TickTimer::start(double secPerTick, std::atomic<bool>* isRunning) {
	*isRunning = true;

	this->secPerTick = secPerTick;
	this->isRunning = isRunning;
	this->lastTime = 0;

	thread = std::thread([&]() { update(); });
}

void TickTimer::update() {
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

bool TickTimer::isTickElapsed() {
	if (tickElapsed) {
		tickElapsed = false;

		return true;
	}

	return false;
}