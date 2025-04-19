#include "Timer.h"

#include <GLFW/glfw3.h>

Timer::Timer()
	: lastTime(0.0f), deltaTime(0.0f), currentTime(0.0f), resetTime(0.0f) {

}

float Timer::getDeltaTime() {
	currentTime = glfwGetTime() - resetTime;
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	return deltaTime;
}

void Timer::reset() {
	resetTime = glfwGetTime();
	lastTime = 0.0f;
}