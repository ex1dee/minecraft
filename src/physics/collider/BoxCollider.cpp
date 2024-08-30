#include "BoxCollider.h"

BoxCollider::BoxCollider(const glm::vec3& extents, const Transform& transform)
	: Collider(ColliderType::BOX, transform) {
	this->extents = extents;

	calcVertices();
}

void BoxCollider::calcVertices() {
	vertices = {
        {0.0f, 0.0f, 0.0f}, 
        {extents.x, 0.0f, 0.0f}, 
        {0.0f, extents.y, 0.0f}, 
        {0.0f, 0.0f, extents.z}, 
        {extents.x, extents.y, extents.z}, 
        {extents.x, 0.0f, extents.z}, 
        {0.0f, extents.y, extents.z}, 
        {extents.x, extents.y, 0.0f}
    };

	glm::mat4 model = calcModel();

	for (glm::vec3& vertex : vertices) {
		vertex = glm::vec3(model * glm::vec4(vertex, 1.0f));
	}
}

std::vector<Rect> BoxCollider::getRectangles(const Transform& transform) {
	std::vector<Rect> rectangles;
	updateTransform(transform);

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

void BoxCollider::updateTransform(const Transform& transform) {
	globalVertices.clear();
	globalVertices.reserve(vertices.size());

	glm::mat4 model = transform.calcModel();

	for (glm::vec3& vertex : vertices) {
		globalVertices.push_back(glm::vec3(model * glm::vec4(vertex, 1.0f)));
	}
}