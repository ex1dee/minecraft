#include "Block.h"

#include "../../math/intersects/RayBoxIntersect.h"

Block::Block(BlockID id) {
	type = BlocksDatabase::get(id);

	if (type->meta != nullptr)
		meta = type->meta->clone();
}

Block::~Block() {
	delete meta;
}

IntersectList Block::intersect(const Ray& ray) const {
	IntersectList intersects;

	Transform transform;
	transform.position = position;

	for (BoxCollider* collider : type->colliders) {
		intersects.add(RayBoxIntersect::intersect(ray, collider, transform));
	}

	return intersects;
}

bool Block::isCollidable() const { 
	return this != nullptr && type->colliders.size(); 
}