#include "Mesh.h"

#include <glm/glm.hpp>

void Mesh::reset() {
	vertexPositions.clear();
	textureCoords.clear();
	normals.clear();
	indices.clear();
}