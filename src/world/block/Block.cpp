#include "Block.h"

#include "../../math/intersects/RayBoxIntersect.h"
#include "../../utils/PointerUtils.h"

Block::Block(Material material) {
	type = BlocksDatabase::get(material);
}

Block::~Block() {
	freePointer(&state);
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