#ifndef MESHDATA_H
#define MESHDATA_H

#include <vector>

enum MeshType;

class MeshData {
public:
	std::vector<Texture> textures;
	std::vector<unsigned int> indices;
	std::vector<float> vertexPositions;
	std::vector<float> textureCoords;
	std::vector<float> normals;

	MeshType type;
	int dimensions;

	MeshData() {}
	MeshData(MeshType type, int dimensions)
		: type(type), dimensions(dimensions) {}

	void reset() {
		vertexPositions.clear();
		textureCoords.clear();
		textures.clear();
		normals.clear();
		indices.clear();
	}
};

#endif