#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

#include "MeshType.h"

struct Mesh {
public:
	std::vector<float> vertexPositions;
	std::vector<float> textureCoords;
	std::vector<unsigned int> indices;

	MeshType type;

	Mesh() {}
	Mesh(MeshType type)
		: type(type) {}

	void reset() {
		vertexPositions.clear();
		textureCoords.clear();
		indices.clear();
	}
};

#endif