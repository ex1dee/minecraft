#include "GUI.h"

#include "../window/Window.h"
#include "InventoryGUI.h"
#include "GUIManager.h"

bool GUI::windowScaled = false;
glm::mat4 GUI::projection;

void GUI::initialize() {
	setup();
}

void GUI::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	setup();

	windowScaled = true;
}

void GUI::setup() {
	setupElements();
	setupProjection();
}

void GUI::setupElements(GUISector* sector) {
	if (sector == nullptr)
		sector = &GUIDatabase::root;

	for (auto pair : *sector) {
		setupElement(*pair.second);
	}
}

void GUI::setupElement(GUIElement& element) {
	if (!element.visible) {
		if (element.hasTexture())
			element.sprite->reset();

		return;
	}

	if (element.hasTexture()) {
		element.sprite->transform.position = scaleByWindow(element.transform.position);
		element.sprite->transform.rotation = element.transform.rotation;
		element.sprite->transform.scale = scaleByWindow(element.transform.scale);

		element.sprite->reset();
		element.sprite->setup();
	}

	if (element.hasText()) {
		element.text->setPosition(scaleByWindow(element.text->getPosition()));
		element.text->setScale(scaleByWindow(element.text->getScale()));
	}

	setupElements(&element.children);
}

void GUI::setupProjection() {
	float halfWidth = Window::getWidth() * 0.5f;
	float halfHeight = Window::getHeight() * 0.5f;

	projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, GUI_ORTHO_NEAR, GUI_ORTHO_FAR);
}

glm::vec3 GUI::scaleByWindow(const glm::vec3& vec) {
	float width = Window::getWidth();
	float height = Window::getHeight();

	return GUIManager::scale(vec, GUI_DEFAULT_WIDTH, GUI_DEFAULT_HEIGHT, width, height);
}

void GUI::update(Player& player) {
	InventoryGUI::update(player, windowScaled);
	
	windowScaled = false;
}