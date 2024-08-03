#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

#include "../../textures/Texture.h"
#include "../../shaders/Shader.h"
#include "MeshData.h"

enum MeshType;

struct Mesh {
	void genVAO();
	void addEBO();
	void addVBO(int dimensions, const std::vector<float>& vertices);
	void bindTextures(Shader* shader);

	std::vector<unsigned int> buffers;
	unsigned int VAO, EBO;
public:
	MeshData data;

	Mesh() {}
	Mesh(const MeshData& data);
	~Mesh();

	void setup();
	void draw(Shader* shader);
	void resetBuffers();
	void reset();
};

enum MeshType {
	CUBE = 0,
	OTHER = 1
};

#endif