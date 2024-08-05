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

	static void gladLoad();
	static void createWindow();
	static void setCallbacks();
	static void setupAntiAliasing();

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
public:
	static int getWidth() { return width; }
	static int getHeight() { return height; }

	static void initialize();
	static void finalize();

	static void swapBuffers();
	static bool shouldClose();
	static void setWindowViewport();
};

#endif