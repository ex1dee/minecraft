#include "Sprite.h"

#include "../../textures/TextureManager.h"

void Sprite::setup() {
	Drawable::setup();

	calcVertices();
	calcTextureCoords();

	addVBO(3, vertexPositions);
	addVBO(2, textureCoords);
	addEBO(indices);
}

void Sprite::calcVertices() {
	glm::vec2 texSize = texture.getSize();
	float width = texSize.x * 0.5f;
	float height = texSize.y * 0.5f;

	vertexPositions.push_back(-width);
	vertexPositions.push_back(-height);
	vertexPositions.push_back(0);

	vertexPositions.push_back(width);
	vertexPositions.push_back(-height);
	vertexPositions.push_back(0);

	vertexPositions.push_back(width);
	vertexPositions.push_back(height);
	vertexPositions.push_back(0);

	vertexPositions.push_back(-width);
	vertexPositions.push_back(height);
	vertexPositions.push_back(0);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);
}

void Sprite::calcTextureCoords() {
	if (texture.useAtlas) {
		texture.atlas.addToTexCoords(textureCoords);
	} else {
		textureCoords.push_back(0);
		textureCoords.push_back(0);

		textureCoords.push_back(1);
		textureCoords.push_back(0);

		textureCoords.push_back(1);
		textureCoords.push_back(1);

		textureCoords.push_back(0);
		textureCoords.push_back(1);
	}
}

void Sprite::draw(Shader& shader) {
	if (texture.data == nullptr)
		return;

	shader.setMat4("model", transform.calcModel());
	shader.setVec4("color", color);
	bindTexture(shader);

	glBindVertexArray(VAO);

	if (indices.size()) {
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
}

void Sprite::bindTexture(Shader& shader) {
	TextureManager::bindTexture(texture.data, shader, "tex");
}

void Sprite::reset() {
	resetBuffers();

	vertexPositions.clear();
	textureCoords.clear();
	indices.clear();
}

void Sprite::resetTexture() {
	if (texture.data != nullptr)
		delete texture.data;
}