#include "Model.h"

Model::~Model() {
	reset();
}

RenderInfo Model::getRenderInfo() {
	return renderInfo;
}

void Model::addMesh(Mesh &mesh, int dimensions) {
	genVAO();

	addVBO(dimensions, mesh.vertexPositions);
	addVBO(2, mesh.textureCoords);
	addVBO(dimensions, mesh.normals);
	addEBO(mesh.indices);
}

void Model::genVAO() {
	if (renderInfo.VAO)
		reset();

	glGenVertexArrays(1, &renderInfo.VAO);
	glBindVertexArray(renderInfo.VAO);
}

void Model::addVBO(int dimensions, const std::vector<float>& vertices) {
	if (!vertices.size())
		return;

	renderInfo.vertexCount = vertices.size();

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(buffers.size(), dimensions, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(buffers.size());

	buffers.push_back(VBO);
}

void Model::addEBO(const std::vector<unsigned int>& indices) {
	if (!indices.size())
		return;

	renderInfo.indicesCount = indices.size();

	if (EBO)
		glDeleteBuffers(1, &EBO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Model::reset() {
	if (renderInfo.VAO)
		glDeleteVertexArrays(1, &renderInfo.VAO);

	if (buffers.size())
		glDeleteBuffers(buffers.size(), buffers.data());

	glDeleteBuffers(1, &EBO);

	EBO = 0;
	buffers.clear();
	renderInfo.reset();
}