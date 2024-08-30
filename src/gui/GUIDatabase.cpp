#include "GUIDatabase.h"

#include "../textures/TextureLoader.h"
#include "../utils/StringConverter.h"
#include "GUIManager.h"

constexpr const char* GUI_DIR = "resources/gui";
constexpr const char* TEXTURES_DIR = "resources/textures/";

GUISector GUIDatabase::root;

void GUIDatabase::initialize() {
	GUISector elements;

	for (const std::string& path : Files::getFolderFiles(GUI_DIR)) {
		std::shared_ptr<GUIElement> element;

		nlohmann::json json = Json::parse(path);
		std::string name = json["name"];

		if (elements.find(name) != elements.end())
			element = elements[name];
		else
			element = std::make_shared<GUIElement>();

		element->visible = json["visible"];
		element->name = name;

		element->transform.position += glm::vec3(Json::toVec2(json["center"]), 0);
		element->transform.rotation += glm::vec3(Json::toVec2(json["rotation"]), 0);
		element->transform.scale *= glm::vec3(Json::toVec2(json["scale"]), 1);
		
		if (json.contains("layer_offset"))
			element->layer_offset = json["layer_offset"];

		addChildren(element, json, elements);

		if (json.contains("texture")) {
			addTexture(*element, json);
		}

		if (json.contains("text")) {
			addText(*element, json);
		}

		elements.emplace(name, element);
	}

	createRootSector(elements);
}

void GUIDatabase::addChildren(std::shared_ptr<GUIElement> element, const nlohmann::basic_json<>& json, GUISector& elements) {
	for (const std::string& childName : json["children"]) {
		std::shared_ptr<GUIElement> child;

		if (elements.find(childName) != elements.end())
			child = elements[childName];
		else
			child = std::make_shared<GUIElement>();

		child->parent = std::shared_ptr<GUIElement>(element);
		child->transform.add(element->transform);
		
		element->children.emplace(childName, child);
		elements.emplace(childName, child);
	}
}

void GUIDatabase::addTexture(GUIElement& element, const nlohmann::basic_json<>& json) {
	nlohmann::basic_json<> atlasJson = json["texture"]["atlas"];
	std::string path = json["texture"]["path"];

	element.sprite = std::make_unique<Sprite>();
	element.sprite->color *= Json::toVec4(json["color"]);

	TextureLoader::loadSprite(json["texture"], element.sprite->texture);
}

void GUIDatabase::addText(GUIElement& element, const nlohmann::basic_json<>& json) {
	glm::vec3 position = glm::vec3(Json::toVec2(json["text"]["position"]), 0);
	glm::vec4 color = Json::toVec4(json["text"]["color"]);
	TextAlignment alignment = json["text"]["alignment"];
	std::string title = json["text"]["content"];

	element.text = std::make_shared<Text2D>(
		StringConverter::toWString(title),
		alignment,
		element.transform.position + position,
		color
	);
}

void GUIDatabase::createRootSector(GUISector& elements) {
	for (auto pair : elements) {
		std::shared_ptr<GUIElement> element = pair.second;

		if (element->parent == nullptr) {
			root.emplace(element->name, element);
		}
	}
}