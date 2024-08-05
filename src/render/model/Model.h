#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "../../math/shapes/AABB.h"
#include "Mesh.h"

class Model {
	std::vector<Mesh*> meshes;

	float shininess;
public:
	AABB aabb;

	Model(float shininess = 0);
	~Model();

	bool isEmpty() { return meshes.empty(); }

	void reset();
	void draw(Shader* shader);
	void addMesh(Mesh* mesh);
	void addMesh(const MeshData& data);
};

#endif