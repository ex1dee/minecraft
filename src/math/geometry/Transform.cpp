#include "Transform.h"

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3& rotateOrigin)
	: position(position), rotation(rotation), scale(scale), rotateOrigin(rotateOrigin) {}

glm::mat4 Transform::calcModel() const {
	glm::mat4 model(1.0f);

	model = glm::translate(model, position + rotateOrigin);

	if (rotation.x != 0) model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	if (rotation.y != 0) model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	if (rotation.z != 0) model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	
	model = glm::translate(model, -rotateOrigin);
	model = glm::scale(model, scale);

	return model;
}

void Transform::add(const Transform& transform) {
	position += transform.position;
	rotation += transform.rotation;
	scale *= transform.scale;
}

void Transform::subtract(const Transform& transform) {
	position -= transform.position;
	rotation -= transform.rotation;
	scale /= transform.scale;
}