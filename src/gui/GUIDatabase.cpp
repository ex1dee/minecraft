#include "GUIDatabase.h"

#include "../textures/TextureLoader.h"

GUISector GUIDatabase::root;

void GUIDatabase::initialize() {
	GUISector elements;

	for (const std::string& path : Files::getFolderFiles(GUI_DIR)) {
		nlohmann::json json = Json::parse(path);

		std::string name = json["name"];
		GUIElement* element;

		if (elements.find(name) != elements.end())
			element = elements[name];
		else
			element = new GUIElement;

		element->hasTexture = json["hasTexture"];
		element->name = name;

		element->transform.position += glm::vec3(Json::toVec2(json["center"]), 0);
		element->transform.rotation += glm::vec3(Json::toVec2(json["rotation"]), 0);
		element->transform.scale *= glm::vec3(Json::toVec2(json["scale"]), 1);

		addChildren(element, json, elements);

		if (element->hasTexture) {
			addTexture(element, json);
		}

		elements.emplace(name, element);
	}

	createRootSector(elements);
}

void GUIDatabase::addChildren(GUIElement* element, const nlohmann::basic_json<>& json, GUISector& elements) {
	for (const std::string& childName : json["children"]) {
		GUIElement* child = new GUIElement;
		child->parent = element;

		child->transform.add(element->transform);
		
		element->children.emplace(childName, child);
		elements.emplace(childName, child);
	}
}

void GUIDatabase::addTexture(GUIElement* element, const nlohmann::basic_json<>& json) {
	nlohmann::basic_json<> atlasJson = json["texture"]["atlas"];
	std::string path = json["texture"]["path"];

	element->sprite = new Sprite;
	element->sprite->color *= Json::toVec4(json["color"]);

	SpriteTexture* texture = &element->sprite->texture;
	texture->useAtlas = atlasJson["use"];

	if (texture->useAtlas) {
		glm::vec2 imagesCount = Json::toVec2(atlasJson["imagesCount"]);
		const TextureAtlas* atlas = TextureLoader::loadAtlas(path, imagesCount, true, TextureType::SPRITE);
		texture->data = (const Texture*)atlas;

		glm::vec2 bottomLeft = Json::toVec2(atlasJson["bottomLeft"]);
		glm::vec2 topRight = Json::toVec2(atlasJson["topRight"]);
		texture->atlas.exactly = atlasJson["exactCoords"];

		if (texture->atlas.exactly) {
			texture->atlas = atlas->getExactTextureCoords(bottomLeft, topRight);
		} else {
			texture->atlas = atlas->getTextureCoords(bottomLeft, topRight);
		}
	} else {
		texture->data = TextureLoader::loadBasic(path, false, TextureType::SPRITE);
	}
}

void GUIDatabase::createRootSector(GUISector& elements) {
	for (auto pair : elements) {
		GUIElement* element = pair.second;

		if (element->parent == nullptr) {
			root.emplace(element->name, element);
		}
	}
}

void GUIDatabase::finalize(GUISector* sector) {
	if (sector == nullptr)
		sector = &root;

	for (auto pair : *sector) {
		GUIElement* element = pair.second;

		for (auto childPair : element->children) {
			GUIElement* child = childPair.second;

			finalize(&child->children);
		}

		delete element;
	}
}