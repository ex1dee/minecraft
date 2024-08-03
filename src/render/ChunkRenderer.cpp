#include "ChunkRenderer.h"

#include "../textures/TextureManager.h"
#include "../world/block/BlocksDatabase.h"
#include "Renderer.h"
#include "Sun.h"

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
	if (solidMeshes.size()) {
		updateSolidShader(camera);
		render(camera, solidMeshes);

		solidMeshes.clear();
	}

	//render(waterMeshes);

	waterMeshes.clear();
}

void ChunkRenderer::updateSolidShader(Camera& camera) {
	defShader->use();

	//defShader->setMat4("projView", Sun::light->getFramebuffer().getProjView());
	defShader->setMat4("projView", camera.getProjView());

	defShader->setInt("pointLightCount", 0);

	defShader->setMat4("sun.shadow.projView", Sun::light->getFramebuffer().getProjView());
	defShader->setVec3("sun.direction", Sun::light->direction);
	defShader->setVec3("sun.color", Sun::light->color);

	TextureManager::bindTexture(BlocksDatabase::textureAtlas, *defShader, "tex", 0);
	TextureManager::bindDepthMap(Sun::light->getFramebuffer().getDepthMap(), *defShader, "sun.shadow.depthMap", 1);
}

void ChunkRenderer::render(Camera& camera, std::vector<ChunkMesh*>& meshes) {
	for (ChunkMesh* mesh : meshes) {
		//if (camera.isAABBInFrustum(mesh->getModel().aabb))
			Renderer::drawElements(mesh->getModel().getRenderInfo());
	}
}

void ChunkRenderer::renderLights() {
	renderLights(solidMeshes);
	//renderLights(waterMeshes);
}

void ChunkRenderer::renderLights(std::vector<ChunkMesh*>& meshes) {
	if (!meshes.size())
		return;

	Sun::light->startRender();

	for (ChunkMesh* mesh : meshes) {
		Renderer::drawElements(mesh->getModel().getRenderInfo());
	}

	Sun::light->finishRender();
}