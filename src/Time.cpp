#include "Time.h"

#include <GLFW/glfw3.h>

float Time::currentTime = 0;
float Time::lastTime = 0;
float Time::deltaTime = 0;
float Time::tickDeltaTime = 0;
float Time::lag = 0; 
bool Time::started = false;

bool Time::needUpdate() {
	if (!started) {
		lastTime = glfwGetTime();
		started = true;
	}

	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	lag += deltaTime;

	if (lag >= SEC_PER_TICK) {
		tickDeltaTime = lag;
		lag -= SEC_PER_TICK;

		return true;
	}
	
	return false;
}