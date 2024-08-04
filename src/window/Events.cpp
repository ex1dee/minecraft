#include "Events.h"

#include <GLFW/glfw3.h>
#include <iostream>

CursorPos Events::cursorPos;
Button Events::keys[1024] = {};
Button Events::mouse[12] = {};
uint64_t Events::frame = 0;

void Events::pollEvents() {
	cursorPos.delta = glm::vec2(0);
	frame++;

	glfwPollEvents();
}

void Events::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		keys[key].pressed = true;
		keys[key].pressFrame = frame;
	} else if (action == GLFW_RELEASE) {
		keys[key].pressed = false;
	}
}

void Events::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		mouse[button].pressed = true;
		mouse[button].pressFrame = frame;
	} else if (action == GLFW_RELEASE) {
		mouse[button].pressed = false;
	}
}

void Events::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	cursorPos.last = cursorPos.current;
	cursorPos.current = glm::vec2(xpos, ypos);
	cursorPos.delta = cursorPos.current - cursorPos.last;
}

bool Events::pressed(int key) {
	return keys[key].pressed;
}

bool Events::justPressed(int key) {
	return keys[key].pressed && keys[key].pressFrame == frame;
}

bool Events::clicked(int mouseButton) {
	return mouse[mouseButton].pressed;
}

bool Events::justClicked(int mouseButton) {
	return mouse[mouseButton].pressed && mouse[mouseButton].pressFrame == frame;
}