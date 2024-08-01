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

void ChunkRenderer::render(Camera& camera, DirectLight* sunLight) {
	updateSolidShader(camera, sunLight);
	render(camera, solidMeshes);

	//render(waterMeshes);

	solidMeshes.clear();
	waterMeshes.clear();
}

void ChunkRenderer::updateSolidShader(Camera& camera, DirectLight* sunLight) {
	defShader->use();

	defShader->setMat4("projView", camera.getProjView());

	defShader->setInt("directLightCount", 1);
	defShader->setMat4("directLight[0].shadow.projView", sunLight->getFramebuffer().getProjView());
	defShader->setVec3("directLight[0].direction", sunLight->direction);
	defShader->setVec3("directLight[0].color", sunLight->color);

	TextureManager::bindTexture(BlocksDatabase::textureAtlas, *defShader, "tex", 0);
	TextureManager::bindDepthMap(sunLight->getFramebuffer().getDepthMap(), *defShader, "directLight[0].shadow.depthMap", 1);
}

void ChunkRenderer::render(Camera& camera, std::vector<ChunkMesh*>& meshes) {
	for (ChunkMesh* mesh : meshes) {
		if (camera.isAABBInFrustum(mesh->getModel().aabb))
			Renderer::drawElements(mesh->getModel().getRenderInfo());
	}
}

void ChunkRenderer::renderLights(DirectLight* sunLight) {
	renderLights(solidMeshes, sunLight);
	//renderLights(waterMeshes, sunLight);
}

void ChunkRenderer::renderLights(std::vector<ChunkMesh*>& meshes, DirectLight* sunLight) {
	sunLight->startRender();

	for (ChunkMesh* mesh : meshes) {
		Renderer::drawElements(mesh->getModel().getRenderInfo());
	}

	sunLight->finishRender();
}