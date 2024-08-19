#ifndef ITEMSDATABASE_H
#define ITEMSDATABASE_H

#include <unordered_map>

#include "ItemType.h"

class ItemsDatabase {
	static std::unordered_map<Material, ItemType*> items;
public:
	static void initialize();
	static void finalize();

	static const ItemType* get(Material material) {
		return items[material];
	}
};

#endif