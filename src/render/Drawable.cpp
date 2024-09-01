#include "Drawable.h"

Drawable::~Drawable() {
	reset();
}

Drawable::Drawable(const Drawable& other) {
	buffers = other.buffers;

	if (other.VAO)
		setup();
}

void Drawable::setup() {
	if (VAO)
		resetBuffers();

	genVAO();
}

void Drawable::genVAO() {
	GL(glGenVertexArrays(1, &VAO));
	GL(glBindVertexArray(VAO));
}

void Drawable::addVBO(int dimensions, const std::vector<float>& vertices, int index) {
	if (!vertices.size())
		return;

	uint32_t VBO;
	GL(glGenBuffers(1, &VBO));
	GL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW));
	
	GL(glVertexAttribPointer(index, dimensions, GL_FLOAT, false, 0, 0));
	GL(glEnableVertexAttribArray(index));

	buffers.push_back(VBO);
}

void Drawable::addEBO(const std::vector<uint32_t>& indices) {
	if (!indices.size())
		return;

	if (EBO)
		glDeleteBuffers(1, &EBO);

	GL(glGenBuffers(1, &EBO));
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW));
}

void Drawable::reset() {
	resetBuffers();
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