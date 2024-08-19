#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <unordered_map>
#include <string>

#include "../render/sprite/Sprite.h"
#include "../utils/PointerUtils.h"
#include "../text/Text2D.h"

constexpr float 
GUI_ELEMENT_Z = -1.0f,
GUI_ELEMENT_LAYER_Z_OFFSET = 0.001f,
GUI_ELEMENT_MAX_LAYER = -GUI_ELEMENT_Z / GUI_ELEMENT_LAYER_Z_OFFSET - 1;

class GUIElement;
typedef std::unordered_map<std::string, GUIElement*> GUISector;

class GUIElement {
public:
	Sprite* sprite;
	Text2D* text;
	Transform transform;
	std::string name;
	int layer_offset;
	bool hasTexture;
	bool hasText;
	bool visible;

	GUIElement* parent;
	GUISector children;

	GUIElement() = default;

	~GUIElement() {
		free(sprite);
		free(text);
	}

	GUIElement(const std::string& name, const Transform& transform, Sprite* sprite, bool visible, GUIElement* parent)
		: name(name), hasTexture(true), hasText(false), transform(transform), 
		  sprite(sprite), visible(visible), parent(parent), text(nullptr) {}

	GUIElement(const std::string& name, Text2D* text, bool visible, GUIElement* parent)
		: name(name), hasTexture(false), hasText(true),  
		  text(text), visible(visible), parent(parent), sprite(nullptr) {}

	GUIElement(const GUIElement& other) {
		if (other.sprite != nullptr)
			sprite = new Sprite(*other.sprite);

		if (other.text != nullptr)
			text = new Text2D(*other.text);

		transform = other.transform;
		name = other.name;
		hasTexture = other.hasTexture;
		visible = other.visible;
		layer_offset = other.layer_offset;

		parent = other.parent;
		children = other.children;
	}
};

#endif