#ifndef EVENTS_H
#define EVENTS_H

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CursorPos.h"
#include "Button.h"

class Events {
	static CursorPos cursorPos;
	static Button keys[1024];
	static Button mouse[12];
	static uint64_t frame;
public:
	static void initialize();
	static void pollEvents();

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

	static CursorPos getCursorPos();
	static bool pressed(int key);
	static bool justPressed(int key);
	static bool clicked(int mouseButton);
	static bool justClicked(int mouseButton);
};

#endif