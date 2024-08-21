#include "MeshData.h"

MeshData::MeshData(MeshType type, int dimensions, uint32_t mode)
	: type(type), dimensions(dimensions), mode(mode) {}

void MeshData::reset() {
	vertexPositions.clear();
	textureCoords.clear();
	textures.clear();
	normals.clear();
	indices.clear();
}