#include "Mesh.h"

#include <glm/glm.hpp>

#include "../../textures/TextureManager.h"

Mesh::Mesh(const MeshData& data)
	: data(data) {
	EBO = 0;
	VAO = 0;
}

Mesh::~Mesh() {
	reset();
}

void Mesh::setup() {
	Drawable::setup();
	
	addVBO(data.dimensions, data.vertexPositions);
	addVBO(3, data.colors);
	addVBO(2, data.textureCoords);
	addVBO(data.dimensions, data.normals);
	addEBO(data.indices);
}

void Mesh::draw(Shader* shader) {
	bindTextures(shader);

	glBindVertexArray(VAO);
	
	if (data.indices.size()) {
		glDrawElements(data.mode, data.indices.size(), GL_UNSIGNED_INT, 0);
	} else if (data.vertexPositions.size()) {
		glDrawArrays(data.mode, 0, data.vertexPositions.size());
	}
}

void Mesh::bindTextures(Shader* shader) {
	int diffuseCount = 0;
	int specularCount = 0;

	for (Texture& texture : data.textures) {
		std::string uniform = "";

		if (texture.getType() == TextureType::DIFFUSE) {
			uniform += "material.diffuse[";
			uniform += std::to_string(diffuseCount++);
		} else if (texture.getType() == TextureType::SPECULAR) {
			uniform += "material.specular[";
			uniform += std::to_string(specularCount++);
		} else {
			continue;
		}

		uniform += "]";
		TextureManager::bindTexture(&texture, *shader, uniform);
	}

	shader->setInt("material.diffuseCount", diffuseCount);
	shader->setInt("material.specularCount", specularCount);
}

void Mesh::reset() {
	resetBuffers();

	data.reset();
}