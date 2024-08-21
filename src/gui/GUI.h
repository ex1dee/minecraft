#ifndef GUI_H
#define GUI_H

#include "../GL/GLHelper.h"
#include <GLFW/glfw3.h>
#include <array>

#include "../items/inventory/Inventory.h"
#include "../player/Player.h"
#include "GUIDatabase.h"

constexpr float
GUI_DEFAULT_WIDTH = 1920.0f,
GUI_DEFAULT_HEIGHT = 1080.0f,
GUI_ORTHO_NEAR = 0.0f,
GUI_ORTHO_FAR = 10.0f;

class GUI {
	static glm::mat4 projection;
	static bool windowScaled;

	static void setup();
	static void setupProjection();
public:
	static void initialize();

	static const glm::mat4& getProjection() { return projection; }
	static const glm::mat4& getView() { return glm::mat4(1); }

	static void update(Player& player);
	static void setupElement(GUIElement& element);
	static glm::vec3 scaleByWindow(const glm::vec3& vec);
	static void setupElements(GUISector* sector = nullptr);
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

#endif