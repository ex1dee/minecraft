#ifndef WINDOW_H
#define WINDOW_H

#include "../GL/GLHelper.h"
#include <GLFW/glfw3.h>

constexpr int
GL_VERSION_MINOR = 3,
GL_VERSION_MAJOR = 3;

class Window {
	static GLFWmonitor* monitor;
	static GLFWwindow* window;
	static bool fullscreen;

	static int screenWidth;
	static int screenHeight;
	static int prevWidth;
	static int prevHeight;
	static int width;
	static int height;

	static void gladLoad();
	static void createWindow();
	static void setCallbacks();
	static void setupScreenSize();
	static void setupDefaultWindowSize();
	static void setupAntiAliasing();

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
public:
	static int getScreenWidth() { return screenWidth; }
	static int getScreenHeight() { return screenHeight; }
	static int getWidth() { return width; }
	static int getHeight() { return height; }

	static void initialize();
	static void finalize();

	static void swapBuffers();
	static bool shouldClose();
	static void toggleFullscreen();
	static void setWindowViewport();
};

#endif