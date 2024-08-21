#include "BlockFrameRenderer.h"

#include <GLFW/glfw3.h>

#include "../shaders/ShadersDatabase.h"

constexpr float BLOCKFRAME_LINE_WIDTH = 3.0f;

BlockFrameRenderer::BlockFrameRenderer() {
	prevBlock = nullptr;
}

void BlockFrameRenderer::render(const Player& player) {
	std::shared_ptr<Block> block = player.getTargetBlock();

	if (prevBlock != block) {
		model.reset();

		if (block != nullptr) {
			createModel(*block, player);
		}

		prevBlock = block;
	}

	if (block != nullptr) {
		render(player.getCamera());
	}
}

void BlockFrameRenderer::render(const Camera& camera) {
	Shader& shader = ShadersDatabase::get(ShaderType::LINE);

	glm::vec3 lineColor(
		glm::abs(sin(glfwGetTime())) + 0.1,
		glm::abs(cos(glfwGetTime())) + 0.1,
		glm::abs(tan(glfwGetTime())) + 0.1
	);

	shader.use();
	shader.setMat4("projView", camera.getProjView());
	shader.setVec3("color", lineColor);

	glLineWidth(BLOCKFRAME_LINE_WIDTH);

	if (!model.isEmpty())
		model.draw(shader);
}

void BlockFrameRenderer::createModel(const Block& block, const Player& player) {
	MeshData meshData(MeshType::CUBE, 3, GL_LINES);
	Transform transform(block.getPosition());

	for (auto& collider : block.getType().colliders) {
		int index = 0;

		for (const Rect& rect : collider->getRectangles(transform)) {
			meshData.vertexPositions.push_back(rect.a.x);
			meshData.vertexPositions.push_back(rect.a.y);
			meshData.vertexPositions.push_back(rect.a.z);

			meshData.vertexPositions.push_back(rect.b.x);
			meshData.vertexPositions.push_back(rect.b.y);
			meshData.vertexPositions.push_back(rect.b.z);

			meshData.vertexPositions.push_back(rect.c.x);
			meshData.vertexPositions.push_back(rect.c.y);
			meshData.vertexPositions.push_back(rect.c.z);

			meshData.vertexPositions.push_back(rect.d.x);
			meshData.vertexPositions.push_back(rect.d.y);
			meshData.vertexPositions.push_back(rect.d.z);

			meshData.indices.push_back(index);
			meshData.indices.push_back(index + 1);

			meshData.indices.push_back(index + 1);
			meshData.indices.push_back(index + 2);

			meshData.indices.push_back(index + 2);
			meshData.indices.push_back(index + 3);

			meshData.indices.push_back(index + 3);
			meshData.indices.push_back(index);

			index += 4;
		}
	}

	model.addMesh(meshData);
}