#include "EntitiesDatabase.h"

#include "../utils/AssimpLoader.h"
#include "../utils/Json.h"

constexpr const char* ENTITIES_DIR = "resources/entities";
constexpr const char* MODELS_DIR = "resources/models";

std::unordered_map<EntityID, std::unique_ptr<EntityType>> EntitiesDatabase::entities;

void EntitiesDatabase::initialize() {
	for (const std::string& path : Files::getFolderFiles(ENTITIES_DIR)) {
		std::unique_ptr<EntityType> type = std::make_unique<EntityType>();
		nlohmann::json json = Json::parse(path);

		type->id = json["id"];
		type->collidesWithObjects = json["physics"]["collidesWithObjects"];
		type->physics = json["physics"]["enabled"];
		type->gravity = json["physics"]["gravity"];
		type->mass = json["physics"]["mass"];

		type->colliderPosition = Json::toVec3(json["collider"]["position"]);
		type->colliderExtents = Json::toVec3(json["collider"]["extents"]);
		
		type->modelTransform.position = Json::toVec3(json["modelTransform"]["position"]);
		type->modelTransform.rotation = Json::toVec3(json["modelTransform"]["rotation"]);
		type->modelTransform.scale = Json::toVec3(json["modelTransform"]["scale"]);

		type->eyesOffset = Json::toVec3(json["eyesOffset"]);

		if (json.contains("model"))
			type->model = AssimpLoader::load(Files::getFullPath(MODELS_DIR, json["model"]["path"]));

		entities[type->id] = std::move(type);
	}
}