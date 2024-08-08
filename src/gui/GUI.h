#ifndef GUI_H
#define GUI_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GUIDatabase.h"

#define GUI_DEFAULT_WIDTH 1920.0f
#define GUI_DEFAULT_HEIGHT 1080.0f
#define GUI_ORTHO_NEAR 0.1f
#define GUI_ORTHO_FAR 10.0f
#define GUI_SPRITE_Z -1

class GUI {
	static glm::mat4 projection;

	static void setup();
	static void setupElements(GUISector* sector = nullptr);
	static void setupProjection();
	static glm::vec3 scaleByWindow(const glm::vec3& vec);
public:
	static void initialize();

	static const glm::mat4& getProjection() { return projection; }
	static const glm::mat4& getView() { return glm::mat4(1); }

	static void update() {}
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

#endif