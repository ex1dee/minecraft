#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: position(position), rotation(rotation), scale(scale) {}

glm::mat4 Transform::calcModel() const {
	glm::mat4 model(1.0f);

	model = glm::mat4_cast(glm::quat(glm::radians(rotation)));
	model = glm::translate(model, position);
	model = glm::scale(model, scale);

	return model;
}

void Transform::add(const Transform& transform) {
	position += transform.position;
	rotation += transform.rotation;
	scale *= transform.scale;
}