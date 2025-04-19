#ifndef INPUT_H
#define INPUT_H

#include "../GL/GLHelper.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CursorPos.h"
#include "Button.h"

class Input {
	static CursorPos cursorPos;
	static Button keys[1024];
	static Button mouse[12];
	static uint64_t frame;
	static double scrollXOffset;
	static double scrollYOffset;
	static uint64_t lastScrollFrame;
public:
	static void pollEvents();

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	static CursorPos getCursorPos() { return cursorPos; }
	static double getScrollXOffset() { return lastScrollFrame == frame ? scrollXOffset : 0.0f; }
	static double getScrollYOffset() { return lastScrollFrame == frame ? scrollYOffset : 0.0f; }

	static bool pressed(int key);
	static bool justPressed(int key);
	static bool clicked(int mouseButton);
	static bool justClicked(int mouseButton);
};

#endif