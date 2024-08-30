#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "../../math/shapes/AABB.h"
#include "Mesh.h"

class Model {
	std::vector<std::unique_ptr<Mesh>> model;

	float shininess;
public:
	AABB aabb;

	Model(float shininess = 0);

	bool isEmpty() { return model.empty() || model[0]->data->vertexPositions.empty(); }

	void reset();
	void draw(Shader& shader);
	void addMesh(std::unique_ptr<MeshData>& data);
};

#endif