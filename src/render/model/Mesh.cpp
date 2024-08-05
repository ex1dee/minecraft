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
	if (VAO)
		resetBuffers();

	genVAO();
	
	addVBO(data.dimensions, data.vertexPositions);
	addVBO(3, data.colors);
	addVBO(2, data.textureCoords);
	addVBO(data.dimensions, data.normals);
	addEBO();
}

void Mesh::genVAO() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Mesh::addVBO(int dimensions, const std::vector<float>& vertices) {
	if (!vertices.size())
		return;

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(buffers.size(), dimensions, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(buffers.size());

	buffers.push_back(VBO);
}

void Mesh::addEBO() {
	if (!data.indices.size())
		return;

	if (EBO)
		glDeleteBuffers(1, &EBO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(unsigned int), data.indices.data(), GL_STATIC_DRAW);
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

	shader->use();

	for (Texture& texture : data.textures) {
		std::string uniform = "";

		if (texture.getType() == DIFFUSE) {
			uniform += "material.diffuse[";
			uniform += std::to_string(diffuseCount++);
		} else if (texture.getType() == SPECULAR) {
			uniform += "material.specular[";
			uniform += std::to_string(specularCount++);
		} else {
			continue;
		}

		uniform += "]";
		TextureManager::bindTexture(texture, *shader, uniform);
	}

	shader->setInt("material.diffuseCount", diffuseCount);
	shader->setInt("material.specularCount", specularCount);
}

void Mesh::reset() {
	resetBuffers();

	data.reset();
}

void Mesh::resetBuffers() {
	if (VAO)
		glDeleteVertexArrays(1, &VAO);

	if (buffers.size())
		glDeleteBuffers(buffers.size(), buffers.data());

	if (EBO)
		glDeleteBuffers(1, &EBO);

	buffers.clear();
	EBO = 0;
	VAO = 0;
}