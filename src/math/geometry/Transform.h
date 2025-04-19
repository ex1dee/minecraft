#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
	glm::vec3 rotateOrigin;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform(
		const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f),
		const glm::vec3& rotateOrigin = glm::vec3(0.0f, 0.0f, 0.0f)
	);

	glm::mat4 calcModel() const;
	void add(const Transform& transform);
	void subtract(const Transform& transform);
};

#endif