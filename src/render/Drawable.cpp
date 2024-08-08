#include "Drawable.h"

void Drawable::setup() {
	if (VAO)
		resetBuffers();

	genVAO();
}

void Drawable::genVAO() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Drawable::addVBO(int dimensions, const std::vector<float>& vertices) {
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

void Drawable::addEBO(const std::vector<unsigned int>& indices) {
	if (!indices.size())
		return;

	if (EBO)
		glDeleteBuffers(1, &EBO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Drawable::resetBuffers() {
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