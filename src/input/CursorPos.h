#ifndef CURSORPOS_H
#define CURSORPOS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct CursorPos {
	glm::vec2 current = glm::vec2(0.0f, 0.0f);
	glm::vec2 last = glm::vec2(0.0f, 0.0f);
	glm::vec2 delta = glm::vec2(0.0f, 0.0f);
};

#endif