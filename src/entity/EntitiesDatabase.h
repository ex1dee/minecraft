#ifndef ENTITIESDATABASE_H
#define ENTITIESDATABASE_H

#include <unordered_map>

#include "EntityType.h"

class EntitiesDatabase {
	static std::unordered_map<EntityID, std::unique_ptr<EntityType>> entities;
public:
	static void initialize();

	static const EntityType& get(EntityID id) const { return *entities[id]; }
};

#endif