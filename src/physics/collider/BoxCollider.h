#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <vector>

#include "Collider.h"

class BoxCollider : public Collider {
	glm::vec3 extents = glm::vec3(0);
	std::vector<glm::vec3> vertices;

	void calcVertices() {
		vertices.clear();

		vertices.push_back({ 0.0f, 0.0f, 0.0f });
		vertices.push_back({ extents.x, 0.0f, 0.0f });
		vertices.push_back({ 0.0f, extents.y, 0.0f });
		vertices.push_back({ 0.0f, 0.0f, extents.z });

		vertices.push_back({ extents.x, 0.0f, extents.z });
		vertices.push_back({ extents.x, extents.y, extents.z });
		vertices.push_back({ 0.0f, extents.y, extents.z });
		vertices.push_back({ extents.x, extents.y, 0.0f });

		glm::mat4 model = calcModel();

		for (glm::vec3& vertex : vertices) {
			vertex = glm::vec3(model * glm::vec4(vertex, 1.0f));
		}
	}
public:
	std::vector<glm::vec3> globalVertices;

	BoxCollider(const glm::vec3& extents, const Transform& transform = Transform())
		: Collider(BOX, transform) {
		this->extents = extents;

		calcVertices();
	}

	void applyTransform(Transform& transform) override {
		globalVertices.clear();

		glm::mat4 model = transform.calcModel();
		
		for (glm::vec3& vertex : vertices) {
			globalVertices.push_back(glm::vec3(model * glm::vec4(vertex, 1.0f)));
		}
	}
};

#endif