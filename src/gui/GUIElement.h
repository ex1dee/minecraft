#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <unordered_map>
#include <string>

#include "../render/sprite/Sprite.h"

class GUIElement;
typedef std::unordered_map<std::string, GUIElement*> GUISector;

class GUIElement {
public:
	Sprite* sprite;
	Transform transform;
	std::string name;
	bool hasTexture;

	GUIElement* parent;
	GUISector children;

	~GUIElement() {
		delete sprite;
	}
};

#endif