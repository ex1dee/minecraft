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