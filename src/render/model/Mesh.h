#ifndef MESH_H
#define MESH_H

#include "../../textures/Texture.h"
#include "../Drawable.h"
#include "MeshData.h"

struct Mesh : public Drawable {
	void bindTextures(Shader& shader);
public:
	std::unique_ptr<MeshData> data;

	Mesh() {}
	Mesh(std::unique_ptr<MeshData>& data);
	~Mesh();

	void setup() override;
	void reset() override;
	void draw(Shader& shader) override;
};

#endif