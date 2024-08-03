#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <glm/glm.hpp>

class Orientation {
public:
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	void update(float yaw, float pitch) {
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		
		update(front);
	}

	void update(const glm::vec3& front) {
		this->front = glm::normalize(front);;

		if (glm::abs(front.y) == 1) {
			right = glm::vec3(1, 0, 0);
			up = glm::vec3(0, 0, 1);
		} else {
			right = glm::normalize(glm::cross(this->front, glm::vec3(0, 1, 0)));
			up = glm::normalize(glm::cross(right, this->front));
		}
	}

	glm::vec3 getMovingFront() const {
		return glm::normalize(glm::vec3(front.x, 0, front.z));
	}

	glm::vec3 getMovingRight() const {
		return glm::normalize(glm::vec3(right.x, 0, right.z));
	}
};

#endif