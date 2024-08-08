#ifndef MESH_H
#define MESH_H

#include "../../textures/Texture.h"
#include "../Drawable.h"
#include "MeshData.h"

enum MeshType;

struct Mesh : public Drawable {
	void bindTextures(Shader* shader);
public:
	MeshData data;

	Mesh() {}
	Mesh(const MeshData& data);
	~Mesh();

	void setup() override;
	void reset() override;
	void draw(Shader* shader) override;
};

enum MeshType {
	CUBE = 0,
	X = 1,
	ASSIMP = 2
};

#endif