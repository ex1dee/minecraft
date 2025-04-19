#include "Orientation.h"

void Orientation::update(float yaw, float pitch) {
	this->yaw = yaw - 360.0f * ((int)yaw / 360);
	this->pitch = pitch - 360.0f * ((int)pitch / 360);

	yaw = glm::radians(yaw);
	pitch = glm::radians(pitch);

	front.x = cos(yaw) * cos(pitch);
	front.y = sin(pitch);
	front.z = sin(yaw) * cos(pitch);

	update(front);
}

void Orientation::update(const glm::vec3& front) {
	this->front = glm::normalize(front);;

	if (glm::abs(front.y) == 1) {
		right = glm::vec3(1, 0, 0);
		up = glm::vec3(0, 0, 1);
	} else {
		right = glm::normalize(glm::cross(this->front, glm::vec3(0, 1, 0)));
		up = glm::normalize(glm::cross(right, this->front));
	}
}