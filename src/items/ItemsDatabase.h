#ifndef ITEMSDATABASE_H
#define ITEMSDATABASE_H

#include <unordered_map>

#include "ItemType.h"

class ItemsDatabase {
	static std::unordered_map<Material, std::unique_ptr<ItemType>> items;
public:
	static void initialize();

	static const ItemType& get(Material material) { return *items[material]; }
	static bool contains(Material material) { return items.find(material) != items.end(); }
};

#endif