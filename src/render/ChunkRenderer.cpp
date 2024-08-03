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
	if (!chunk.solid->getModel().isEmpty())
		solidMeshes.push_back(chunk.solid);

	if (!chunk.water->getModel().isEmpty())
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
	activeShader = defShader;
	activeShader->use();

	//defShader->setMat4("projView", sun.getLight().getFramebuffer().getProjView())
	activeShader->setMat4("projView", camera->getProjView());
	activeShader->setVec3("cameraPos", camera->getPosition());
	activeShader->setInt("pointLightCount", 0);

	activeShader->setMat4("sun.shadow.projView", sun.getLight().getFramebuffer().getProjView());
	activeShader->setVec3("sun.direction", sun.getLight().direction);
	activeShader->setVec3("sun.color", sun.getLight().color);
	
	TextureManager::bindTexture(BlocksDatabase::getTextureAtlas(), *activeShader, "tex");
	TextureManager::bindDepthMap(sun.getLight().getFramebuffer().getDepthMap(), *activeShader, "sun.shadow.depthMap");
}

void ChunkRenderer::render(std::vector<ChunkMesh*>& meshes, Camera* camera, bool onlyVisible) {
	for (ChunkMesh* mesh : meshes) {
		if (!onlyVisible || camera->isAABBInFrustum(mesh->getModel().aabb)) {
			mesh->getModel().draw(activeShader);
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

	activeShader = sun.getLight().getFramebuffer().getShader();

	sun.getLight().startRender();
	render(meshes);
	sun.getLight().finishRender();
}