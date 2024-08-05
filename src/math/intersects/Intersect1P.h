#ifndef INTERSECT1P_H
#define INTERSECT1P_H

#include <glm/glm.hpp>

#define UNDEFINED_POINT glm::vec3(FLT_MAX)

class Intersect1P {
public:
	bool intersected;
	glm::vec3 point = UNDEFINED_POINT;
};

#endif