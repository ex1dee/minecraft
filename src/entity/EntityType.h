#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H

#include <map>

#include "../animation/skeletal/Animator.h"
#include "../render/model/Model.h"
#include "EntityID.h"

class EntityType {
public:
	EntityID id;
	std::map<std::string, std::shared_ptr<Animation>> animations;
	std::shared_ptr<Model> model;
	glm::vec3 colliderPosition;
	glm::vec3 colliderExtents;
	glm::vec3 eyesOffset;
	Transform modelTransform;
	float mass;
	bool collidesWithObjects;
	bool isInCameraSpace;
	bool physics;
	bool gravity;
};

#endif