#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <vector>

#include "RenderInfo.h"
#include "Mesh.h"

class Model {
	void genVAO();
	void addVBO(int dimensions, const std::vector<float> &vertices);
	void addEBO(const std::vector<unsigned int> &indices);

	std::vector<unsigned int> buffers;
	RenderInfo renderInfo;
	unsigned int EBO;
	unsigned int FBO;
public:
	Model() = default;
	~Model();

	RenderInfo getRenderInfo();
	void addMesh(Mesh& mesh, int dimensions);
	void reset();
};

#endif