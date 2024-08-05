#include "BoxCollider.h"

BoxCollider::BoxCollider(const glm::vec3& extents, const Transform& transform)
	: Collider(BOX, transform) {
	this->extents = extents;

	calcVertices();
}

void BoxCollider::calcVertices() {
	vertices.clear();

	vertices.push_back({ 0.0f, 0.0f, 0.0f });
	vertices.push_back({ extents.x, 0.0f, 0.0f });
	vertices.push_back({ 0.0f, extents.y, 0.0f });
	vertices.push_back({ 0.0f, 0.0f, extents.z });

	vertices.push_back({ extents.x, extents.y, extents.z });
	vertices.push_back({ extents.x, 0.0f, extents.z });
	vertices.push_back({ 0.0f, extents.y, extents.z });
	vertices.push_back({ extents.x, extents.y, 0.0f });

	glm::mat4 model = calcModel();

	for (glm::vec3& vertex : vertices) {
		vertex = glm::vec3(model * glm::vec4(vertex, 1.0f));
	}
}
#include <iostream>
std::vector<Rect> BoxCollider::getRectangles(const Transform& transform) {
	std::vector<Rect> rectangles;
	applyTransform(transform);

	for (int i = 0; i <= 4; i += 4) {
		rectangles.push_back(Rect(
			globalVertices[i],
			globalVertices[i + 1],
			globalVertices[5 - i],
			globalVertices[i + 3]
		));

		rectangles.push_back(Rect(
			globalVertices[i],
			globalVertices[i + 2],
			globalVertices[6 - i],
			globalVertices[i + 3]
		));

		rectangles.push_back(Rect(
			globalVertices[i],
			globalVertices[i + 1],
			globalVertices[7 - i],
			globalVertices[i + 2]
		));
	}

	return rectangles;
}

void BoxCollider::applyTransform(const Transform& transform) {
	globalVertices.clear();

	glm::mat4 model = transform.calcModel();

	for (glm::vec3& vertex : vertices) {
		globalVertices.push_back(glm::vec3(model * glm::vec4(vertex, 1.0f)));
	}
}