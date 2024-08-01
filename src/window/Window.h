#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GL_VERSION_MINOR 3
#define GL_VERSION_MAJOR 3

class Window {
	static GLFWwindow* window;

	static int width;
	static int height;

	static void createWindow();
	static void setCallbacks();
	static void gladLoad();

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
public:
	static void initialize();
	static void finalize();
	static void swapBuffers();
	static void setWindowViewport();
	static bool shouldClose();
	static int getWidth();
	static int getHeight();
};

#endif