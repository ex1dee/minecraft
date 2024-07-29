#include "ChunkRenderer.h"

#include "../textures/TextureManager.h"
#include "../world/block/BlocksDatabase.h"
#include "Renderer.h"

ChunkRenderer::ChunkRenderer() {
	defShader = new Shader("shaders/default.vs", "shaders/default.fs");
}

ChunkRenderer::~ChunkRenderer() {
	delete defShader;
}

void ChunkRenderer::add(ChunkMeshCollection& chunk) {
	if (chunk.solid->getModel().getRenderInfo().indicesCount)
		solidMeshes.push_back(chunk.solid);

	if (chunk.water->getModel().getRenderInfo().indicesCount)
		waterMeshes.push_back(chunk.water);
}

void ChunkRenderer::render(Camera& camera, const glm::vec3& lightDir) {
	if (solidMeshes.size()) {
		updateSolidShader(camera, lightDir);
		render(solidMeshes);
	}

	render(waterMeshes);

	solidMeshes.clear();
	waterMeshes.clear();
}

void ChunkRenderer::render(std::vector<ChunkMesh*>& meshes) {
	for (ChunkMesh* mesh : meshes) {
		Renderer::drawElements(mesh->getModel().getRenderInfo());
	}
}

void ChunkRenderer::updateSolidShader(Camera& camera, const glm::vec3& lightDir) {
	activeShader = defShader;
	activeShader->use();

	activeShader->setMat4("view", camera.getView());
	activeShader->setMat4("projection", camera.getProjection());
	activeShader->setVec3("lightDir", lightDir);

	TextureManager::bindTexture(BlocksDatabase::textureAtlas, *activeShader, "tex", 0);
}