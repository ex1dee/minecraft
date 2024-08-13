#ifndef ENTITIESDATABASE_H
#define ENTITIESDATABASE_H

#include <unordered_map>

#include "EntityType.h"

class EntitiesDatabase {
	static std::unordered_map<EntityID, EntityType*> entities;
public:
	static void initialize();
	static void finalize();

	static EntityType* const get(EntityID id) { return entities[id]; }
};

#endif