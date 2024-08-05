#include "Block.h"

#include "../../math/intersects/RayBoxIntersect.h"

Block::Block(BlockID id) {
	type = BlocksDatabase::get(id);
}

IntersectList Block::intersect(const Ray& ray) const {
	IntersectList intersects;
	
	for (BoxCollider* collider : type->colliders) {
		intersects.add(RayBoxIntersect::intersect(ray, collider, transform));
	}

	return intersects;
}