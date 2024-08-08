#include "GUI.h"

#include "../window/Window.h"

glm::mat4 GUI::projection;

void GUI::initialize() {
	setup();
}

void GUI::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	setup();
}

void GUI::setup() {
	setupElements();
	setupProjection();
}

void GUI::setupElements(GUISector* sector) {
	if (sector == nullptr)
		sector = &GUIDatabase::root;

	for (auto pair : *sector) {
		GUIElement* element = pair.second;

		if (element->hasTexture) {
			element->sprite->transform.position = scaleByWindow(element->transform.position);
			element->sprite->transform.rotation = element->transform.rotation;
			element->sprite->transform.scale = scaleByWindow(element->transform.scale);

			element->sprite->reset();
			element->sprite->setup();
		}

		setupElements(&element->children);
	}
}

void GUI::setupProjection() {
	float width = Window::getWidth() * 0.5f;
	float height = Window::getHeight() * 0.5f;

	projection = glm::ortho(-width, width, -height, height, GUI_ORTHO_NEAR, GUI_ORTHO_FAR);
}

glm::vec3 GUI::scaleByWindow(const glm::vec3& vec) {
	float width = Window::getWidth();
	float height = Window::getHeight();

	return glm::vec3(
		(width / GUI_DEFAULT_WIDTH) * vec.x,
		(height / GUI_DEFAULT_HEIGHT) * vec.y,
		GUI_SPRITE_Z
	);
}