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

void ChunkRenderer::add(const ChunkMeshCollection& chunk) {
	if (chunk.solid->getModel().getRenderInfo().indicesCount)
		solidMeshes.push_back(chunk.solid);

	if (chunk.water->getModel().getRenderInfo().indicesCount)
		waterMeshes.push_back(chunk.water);
}

void ChunkRenderer::render(Camera* camera, const Sun& sun) {
	if (solidMeshes.size()) {
		updateSolidShader(camera, sun);
		render(solidMeshes, camera, true);

		solidMeshes.clear();
	}

	//render(waterMeshes);

	waterMeshes.clear();
}

void ChunkRenderer::updateSolidShader(Camera* camera, const Sun& sun) {
	defShader->use();

	//defShader->setMat4("projView", sun.getLight().getFramebuffer().getProjView())
	defShader->setMat4("projView", camera->getProjView());

	defShader->setInt("pointLightCount", 0);

	defShader->setMat4("sun.shadow.projView", sun.getLight().getFramebuffer().getProjView());
	defShader->setVec3("sun.direction", sun.getLight().direction);
	defShader->setVec3("sun.color", sun.getLight().color);

	TextureManager::bindTexture(BlocksDatabase::textureAtlas, *defShader, "tex", 0);
	TextureManager::bindDepthMap(sun.getLight().getFramebuffer().getDepthMap(), *defShader, "sun.shadow.depthMap", 1);
}

void ChunkRenderer::render(std::vector<ChunkMesh*>& meshes, Camera* camera, bool onlyVisible) {
	for (ChunkMesh* mesh : meshes) {
		if (!onlyVisible || camera->isAABBInFrustum(mesh->getModel().aabb)) {
			Renderer::drawElements(mesh->getModel().getRenderInfo());
		}
	}
}

void ChunkRenderer::renderLights(const Sun& sun) {
	renderLights(solidMeshes, sun);
	//renderLights(waterMeshes);
}

void ChunkRenderer::renderLights(std::vector<ChunkMesh*>& meshes, const Sun& sun) {
	if (!meshes.size())
		return;

	sun.getLight().startRender();
	render(meshes);
	sun.getLight().finishRender();
}