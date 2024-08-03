#include "Model.h"

Model::Model(float shininess)
	: shininess(shininess) {

}

Model::~Model() {
	reset();
}

void Model::addMesh(const MeshData& data) {
	Mesh* mesh = new Mesh(data);
	mesh->setup();

	meshes.push_back(mesh);
}

void Model::draw(Shader* shader) {
	for (Mesh* mesh : meshes) {
		mesh->draw(shader);
	}
}

void Model::reset() {
	for (Mesh* mesh : meshes) {
		delete mesh;
	}

	meshes.clear();
}