#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <vector>

#include "RenderInfo.h"
#include "mesh/Mesh.h"

class Model {
	void genVAO();
	void addVBO(int dimensions, const std::vector<float> &vertices);
	void addEBO(const std::vector<unsigned int> &indices);

	std::vector<unsigned int> buffers;
	RenderInfo renderInfo;
	unsigned int EBO;
public:
	Model() = default;
	~Model();

	RenderInfo getRenderInfo();
	void addMesh(Mesh& mesh);
	void reset();
};

#endif