#include "Input.h"

#include <GLFW/glfw3.h>

double Input::scrollXOffset = 0;
double Input::scrollYOffset = 0;
uint64_t Input::lastScrollFrame = 0;
uint64_t Input::frame = 0;
Button Input::keys[1024] = {};
Button Input::mouse[12] = {};
CursorPos Input::cursorPos;

void Input::pollEvents() {
	cursorPos.delta = glm::vec2(0);
	frame++;

	glfwPollEvents();
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		keys[key].pressed = true;
		keys[key].pressFrame = frame;
	} else if (action == GLFW_RELEASE) {
		keys[key].pressed = false;
	}
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		mouse[button].pressed = true;
		mouse[button].pressFrame = frame;
	} else if (action == GLFW_RELEASE) {
		mouse[button].pressed = false;
	}
}

void Input::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	cursorPos.last = cursorPos.current;
	cursorPos.current = glm::vec2(xpos, ypos);
	cursorPos.delta = cursorPos.current - cursorPos.last;
}

void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	scrollXOffset = xoffset;
	scrollYOffset = yoffset;
	lastScrollFrame = frame;
}

bool Input::pressed(int key) {
	return keys[key].pressed;
}

bool Input::justPressed(int key) {
	return keys[key].pressed && keys[key].pressFrame == frame;
}

bool Input::clicked(int mouseButton) {
	return mouse[mouseButton].pressed;
}

bool Input::justClicked(int mouseButton) {
	return mouse[mouseButton].pressed && mouse[mouseButton].pressFrame == frame;
}