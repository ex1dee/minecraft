#ifndef MESHDATA_H
#define MESHDATA_H

#include <vector>

#include "../../textures/Texture.h"
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
	MeshData(MeshType type, int dimensions, uint32_t mode = GL_TRIANGLES);

	MeshData(MeshData&& other) = default;
	MeshData& operator=(MeshData&& other) = default;

	void reset();
};

#endif