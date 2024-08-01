#include "Mesh.h"

#include <glm/glm.hpp>

void Mesh::calcNormals() {
	if (vertexPositions.size() < 9)
		return;

	for (int i = 9; i < vertexPositions.size(); i += 18) {
		glm::vec3 a = glm::vec3(vertexPositions[i - 9], vertexPositions[i - 8], vertexPositions[i - 7]);
		glm::vec3 b = glm::vec3(vertexPositions[i - 6], vertexPositions[i - 5], vertexPositions[i - 4]);
		glm::vec3 c = glm::vec3(vertexPositions[i - 3], vertexPositions[i - 2], vertexPositions[i - 1]);

		glm::vec3 ab = b - a;
		glm::vec3 ac = c - a;

		glm::vec3 normal = glm::normalize(glm::cross(ab, ac));

		for (int j = 0; j < 6; ++j) {
			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);
		}
	}
}

void Mesh::reset() {
	vertexPositions.clear();
	textureCoords.clear();
	normals.clear();
	indices.clear();
}