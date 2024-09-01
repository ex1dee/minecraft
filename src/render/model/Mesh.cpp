#include "Mesh.h"

#include <glm/glm.hpp>

#include "../../textures/TextureManager.h"

Mesh::Mesh(std::unique_ptr<MeshData>& data)
	: data(std::move(data)) {
	EBO = 0;
	VAO = 0;
}

Mesh::~Mesh() {
	reset();
}

void Mesh::setup() {
	Drawable::setup();
	
	addVBO(data->dimensions, data->vertexPositions, 0);
	addVBO(data->dimensions, data->normals, 1);
	addVBO(2, data->textureCoords, 2);
	addVBO(4, data->colors, 3);
	addEBO(data->indices);
}

void Mesh::draw(Shader& shader) {
	shader.setBool("useColors", !data->colors.empty());
	bindTextures(shader);

	glBindVertexArray(VAO);
	
	if (data->indices.size()) {
		glDrawElements(data->mode, data->indices.size(), GL_UNSIGNED_INT, 0);
	} else if (data->vertexPositions.size()) {
		glDrawArrays(data->mode, 0, data->vertexPositions.size());
	}
}

void Mesh::bindTextures(Shader& shader) {
	int diffuseCount = 0;
	int specularCount = 0;

	for (auto& texture : data->textures) {
		std::string uniform = "";

		if (texture->getType() == TextureType::DIFFUSE) {
			uniform += "material.diffuse[";
			uniform += std::to_string(diffuseCount++);
		} else if (texture->getType() == TextureType::SPECULAR) {
			uniform += "material.specular[";
			uniform += std::to_string(specularCount++);
		} else {
			continue;
		}

		uniform += "]";
		TextureManager::bindTexture(*texture, shader, uniform);
	}

	shader.setInt("material.diffuseCount", diffuseCount);
	shader.setInt("material.specularCount", specularCount);
}

void Mesh::reset() {
	Drawable::reset();

	data->reset();
}