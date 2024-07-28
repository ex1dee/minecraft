#ifndef BLOCKFACES_H
#define BLOCKFACES_H

#include <glm/glm.hpp>

struct BlockFaces {
	glm::vec3 top;
	glm::vec3 bottom;
	glm::vec3 right;
	glm::vec3 left;
	glm::vec3 front;
	glm::vec3 back;

	BlockFaces(glm::vec3& pos) {
		top = glm::vec3(pos.x, pos.y + 1, pos.z);
		bottom = glm::vec3(pos.x, pos.y - 1, pos.z);
		right = glm::vec3(pos.x + 1, pos.y, pos.z);
		left = glm::vec3(pos.x - 1, pos.y, pos.z);
		front = glm::vec3(pos.x, pos.y, pos.z + 1);
		back = glm::vec3(pos.x, pos.y, pos.z - 1);
	}
};

#endif