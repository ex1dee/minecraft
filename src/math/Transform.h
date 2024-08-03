#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f))
		: position(position), rotation(rotation), scale(scale) {}

	glm::mat4 calcModel() {
		glm::mat4 model(1.0f);
		
		if (rotation.x != 0) model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		if (rotation.y != 0) model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		if (rotation.z != 0) model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

		model = glm::translate(model, position);
		model = glm::scale(model, scale);

		return model;
	}
};

#endif