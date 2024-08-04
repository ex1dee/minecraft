#ifndef ENTITIESDATABASE_H
#define ENTITIESDATABASE_H

#define ENTITIES_DIR "resources/entities"
#define MODELS_DIR "resources/models"

#include <unordered_map>

#include "EntityType.h"

class EntitiesDatabase {
	static std::unordered_map<EntityID, EntityType*> entities;
public:
	static void initialize();
	static void finalize();

	static EntityType* get(EntityID id) { return entities[id]; }
};

#endif