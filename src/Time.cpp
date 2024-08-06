#include "Time.h"

#include <GLFW/glfw3.h>

float Time::currentTime = 0;
float Time::lastTime = 0;
float Time::deltaTime = 0;
float Time::tickLag = 0; 
float Time::physicsTickLag = 0;
bool Time::physicsTickElapsed = false;
bool Time::tickElapsed = false;
bool Time::started = false;
#include <iostream>
void Time::update() {
	if (!started) {
		lastTime = glfwGetTime();
		started = true;
	}

	tickElapsed = false;
	physicsTickElapsed = false;

	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	tickLag += deltaTime;

	if (tickLag >= SEC_PER_TICK) {
		tickElapsed = true;
		tickLag = 0;
	}

	physicsTickLag += deltaTime;

	if (physicsTickLag >= SEC_PER_PHYSICS_TICK) {
		physicsTickElapsed = true;
		physicsTickLag = 0;
	}
}