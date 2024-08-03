#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <vector>

#include "../../math/AABB.h"
#include "Mesh.h"

class Model {
	std::vector<Mesh*> meshes;

	float shininess;
public:
	AABB aabb;

	Model(float shininess = 0);
	~Model();

	bool isEmpty() { return meshes.empty(); }

	void draw(Shader* shader);
	void addMesh(const MeshData& data);
	void reset();
};

#endif