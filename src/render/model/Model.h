#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "../../math/shapes/AABB.h"
#include "Mesh.h"

class Model {
protected:
	std::vector<std::unique_ptr<Mesh>> meshes;

	float shininess;
public:
	AABB aabb;

	Model(float shininess = 0);
	virtual ~Model() = default;

	bool isEmpty() { return meshes.empty() || meshes[0]->data->vertexPositions.empty(); }

	virtual void reset();
	virtual void draw(Shader& shader);

	void addMesh(std::unique_ptr<MeshData>& data);
};

#endif