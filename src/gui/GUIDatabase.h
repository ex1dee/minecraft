#ifndef GUIDATABASE_H
#define GUIDATABASE_H

#include "../utils/Json.h"
#include "GUIElement.h"

class GUIDatabase {
	static void createRootSector(GUISector& elements);
	static void addTexture(GUIElement* element, const nlohmann::basic_json<>& json);
	static void addChildren(GUIElement* element, const nlohmann::basic_json<>& json, GUISector& elements);
public:
	static GUISector root;

	static void initialize();
	static void finalize(GUISector* sector = nullptr);
};

#endif