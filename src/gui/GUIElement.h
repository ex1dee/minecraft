#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <unordered_map>
#include <string>

#include "../render/sprite/Sprite.h"
#include "../text/Text2D.h"

constexpr float 
GUI_ELEMENT_Z = -1.0f,
GUI_ELEMENT_LAYER_Z_OFFSET = 0.001f,
GUI_ELEMENT_MAX_LAYER = -GUI_ELEMENT_Z / GUI_ELEMENT_LAYER_Z_OFFSET - 1;

class GUIElement;
typedef std::unordered_map<std::string, std::shared_ptr<GUIElement>> GUISector;

class GUIElement {
public:
	std::unique_ptr<Sprite> sprite;
	std::unique_ptr<Text2D> text;
	int layer_offset = 0;
	Transform transform;
	std::string name;
	bool hasTexture;
	bool hasText;
	bool visible;

	std::shared_ptr<GUIElement> parent;
	GUISector children;

	GUIElement() = default;

	GUIElement(const std::string& name, const Transform& transform, std::unique_ptr<Sprite>& sprite, bool visible, std::shared_ptr<GUIElement>& parent)
		: name(name), hasTexture(true), hasText(false), transform(transform),
		sprite(std::move(sprite)), visible(visible), parent(parent), text(nullptr) {}	

	GUIElement(const std::string& name, std::unique_ptr<Text2D>& text, bool visible, std::shared_ptr<GUIElement>& parent)
		: name(name), hasTexture(false), hasText(true),  
		  text(std::move(text)), visible(visible), parent(parent), sprite(nullptr) {}

	GUIElement(const GUIElement& other) {
		if (other.sprite != nullptr)
			sprite = std::make_unique<Sprite>(*other.sprite);

		if (other.text != nullptr)
			text = std::make_unique<Text2D>(*other.text);

		transform = other.transform;
		name = other.name;
		hasTexture = other.hasTexture;
		hasText = other.hasText;
		visible = other.visible;
		layer_offset = other.layer_offset;

		parent = other.parent;
		children = other.children;
	}
};

#endif