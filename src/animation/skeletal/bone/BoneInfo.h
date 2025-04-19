#ifndef BONEINFO_H
#define BONEINFO_H

#include <glm/glm.hpp>

class BoneInfo {
public:
	int id;
	glm::mat4 offset;
};

#endif