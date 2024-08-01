#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <vector>

#include "../math/AABB.h"
#include "RenderInfo.h"
#include "Mesh.h"

class Model {
	void genVAO();
	void addVBO(int dimensions, const std::vector<float> &vertices);
	void addEBO(const std::vector<unsigned int> &indices);

	std::vector<unsigned int> buffers;
	RenderInfo renderInfo;
	unsigned int EBO;
public:
	AABB aabb;

	Model() {}
	~Model();

	RenderInfo getRenderInfo();
	void reset();
	void addMesh(Mesh& mesh, int dimensions);
};

#endif