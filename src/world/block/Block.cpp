#include "Block.h"

#include "../../math/intersects/RayBoxIntersect.h"

Block::Block(Material material)
	: material(material) {
	assert(BlocksDatabase::contains(material));
}

IntersectList Block::intersect(const Ray& ray) const {
	IntersectList intersects;

	Transform transform;
	transform.position = position;

	for (auto& collider : getType().colliders) {
		intersects.add(RayBoxIntersect::intersect(ray, *collider, transform));
	}

	return intersects;
}

bool Block::isCollidable() const { 
	return !getType().colliders.empty();
}

bool Block::isLiquid() const { 
	return getMeta<Liquid>(this) != nullptr; 
}