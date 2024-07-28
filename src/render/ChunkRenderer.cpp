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

void ChunkRenderer::render(Camera& camera) {
	activeShader = defShader;
	render(camera, solidMeshes);

	activeShader = defShader;
	render(camera, waterMeshes);

	solidMeshes.clear();
	waterMeshes.clear();
}

void ChunkRenderer::render(Camera& camera, std::vector<ChunkMesh*>& meshes) {
	if (!meshes.size())
		return;

	activeShader->use();
	
	TextureManager::bindTexture(BlocksDatabase::textureAtlas, *activeShader, "tex", 0);

	activeShader->setMat4("view", camera.getView());
	activeShader->setMat4("projection", camera.getProjection());

	for (ChunkMesh* mesh : meshes) {
		Renderer::drawElements(mesh->getModel().getRenderInfo());
	}
}