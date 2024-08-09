#ifndef MESHDATA_H
#define MESHDATA_H

#include <vector>

#include "MeshType.h"

class MeshData {
public:
	std::vector<Texture> textures;
	std::vector<uint32_t> indices;
	std::vector<float> vertexPositions;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	std::vector<float> colors;

	MeshType type;
	int dimensions;
	uint32_t mode;

	MeshData() {}
	MeshData(MeshType type, int dimensions, uint32_t mode = GL_TRIANGLES)
		: type(type), dimensions(dimensions), mode(mode) {}

	void reset() {
		vertexPositions.clear();
		textureCoords.clear();
		textures.clear();
		normals.clear();
		indices.clear();
	}
};

#endif