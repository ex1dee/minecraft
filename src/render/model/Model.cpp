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

	addMesh(mesh);
}

void Model::addMesh(Mesh* mesh) {
	meshes.push_back(mesh);
}

void Model::draw(Shader* shader) {
	for (Mesh* mesh : meshes) {
		if (mesh != nullptr)
			mesh->draw(shader);
	}
}

void Model::reset() {
	for (Mesh* mesh : meshes) {
		delete mesh;
	}

	meshes.clear();
}