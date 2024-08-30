#include "Model.h"

Model::Model(float shininess)
	: shininess(shininess) {

}

void Model::addMesh(std::unique_ptr<MeshData>& data) {
	std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>(data);
	mesh->setup();

	model.push_back(std::move(mesh));
}

void Model::draw(Shader& shader) {
	for (auto& mesh : model) {
		mesh->draw(shader);
	}
}

void Model::reset() {
	model.clear();
}