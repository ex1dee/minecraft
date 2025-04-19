#ifndef MESHDATA_H
#define MESHDATA_H

#include <vector>

#include "../../animation/AnimationConstants.h"
#include "../../textures/Texture.h"
#include "MeshType.h"

class MeshData {
public:
	std::vector<uint32_t> indices;
	std::vector<std::shared_ptr<Texture>> textures;
	std::vector<int> vertexBoneIDs;
	std::vector<float> vertexBoneWeights;
	std::vector<float> vertexPositions;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	std::vector<float> colors;

	MeshType type;
	int dimensions;
	uint32_t mode;

	MeshData() {}
	MeshData(MeshType type, int dimensions, uint32_t mode = GL_TRIANGLES);

	void reset();
};

#endif