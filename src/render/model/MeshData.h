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
	std::vector<float> colors;

	MeshType type;
	int dimensions;
	unsigned int mode;

	MeshData() {}
	MeshData(MeshType type, int dimensions, unsigned int mode = GL_TRIANGLES)
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