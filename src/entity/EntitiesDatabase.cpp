#include "EntitiesDatabase.h"

#include "../utils/AssimpLoader.h"
#include "../utils/Json.h"

std::unordered_map<EntityID, EntityType*> EntitiesDatabase::entities;

void EntitiesDatabase::initialize() {
	for (std::string path : Files::getFolderFiles(ENTITIES_DIR)) {
		nlohmann::json json = Json::parse(path.c_str());

		EntityType* type = new EntityType;
		type->id = json["id"];
		type->physics = json["physics"]["enabled"];
		type->gravity = json["physics"]["gravity"];
		type->mass = json["physics"]["mass"];

		type->colliderPosition = Json::toVec3(json["collider"]["position"]);
		type->colliderExtents = Json::toVec3(json["collider"]["extents"]);
		
		type->offset.position = Json::toVec3(json["offset"]["position"]);
		type->offset.rotation = Json::toVec3(json["offset"]["rotation"]);
		type->offset.scale = Json::toVec3(json["offset"]["scale"]);

		type->eyesOffset = Json::toVec3(json["eyes_offset"]);

		std::string modelPath = json["model"]["path"];
		type->model = AssimpLoader::load(Files::getFullPath(MODELS_DIR, modelPath.c_str()));

		entities[type->id] = type;
	}
}

void EntitiesDatabase::finalize() {
	for (std::pair<int, EntityType*> pair : entities) {
		delete pair.second;
	}
}