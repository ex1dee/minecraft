#include "ChunkRenderer.h"

#include "../textures/TextureManager.h"
#include "../world/block/BlocksDatabase.h"
#include "../shaders/ShadersDatabase.h"
#include "Renderer.h"

void ChunkRenderer::add(const ChunkMeshCollection& chunk) {
	if (!chunk.solid->getModel().isEmpty())
		solidMeshes.push_back(chunk.solid);

	if (!chunk.water->getModel().isEmpty())
		waterMeshes.push_back(chunk.water);

	if (!chunk.flora->getModel().isEmpty())
		floraMeshes.push_back(chunk.flora);
}

void ChunkRenderer::render(Camera* camera, const Sun& sun) {
	if (solidMeshes.size()) {
		updateSolidShader(camera, sun);
		render(solidMeshes, camera, true);

		solidMeshes.clear();
	}

	updateFloraShader(camera, sun);

	if (floraMeshes.size()) {
		updateFloraShader(camera, sun);

		Renderer::startTransparentRender();
		render(floraMeshes, camera, true);
		Renderer::finishTransparentRender();

		floraMeshes.clear();
	}

	//render(waterMeshes);

	waterMeshes.clear();
}

void ChunkRenderer::updateSolidShader(Camera* camera, const Sun& sun) {
	activeShader = ShadersDatabase::get(DEFAULT);
	activeShader->use();

	//defShader->setMat4("projView", sun.getLight().getFramebuffer().getProjView())
	activeShader->setMat4("projView", camera->getProjView());
	activeShader->setMat4("model", glm::mat4(1));
	activeShader->setVec3("cameraPos", camera->getPosition());

	activeShader->setBool("material.shadow", true);
	activeShader->setBool("material.lighting", true);

	activeShader->setMat4("sun.shadow.projView", sun.getLight().getFramebuffer().getProjView());
	activeShader->setVec3("sun.direction", sun.getLight().direction);
	activeShader->setVec3("sun.color", sun.getLight().color);
	
	activeShader->setInt("pointLightCount", 0);

	TextureManager::bindTexture(BlocksDatabase::getTextureAtlas(), *activeShader, "tex");
	TextureManager::bindDepthMap(sun.getLight().getFramebuffer().getDepthMap(), *activeShader, "sun.shadow.depthMap");
}

void ChunkRenderer::updateFloraShader(Camera* camera, const Sun& sun) {
	activeShader = ShadersDatabase::get(DEFAULT);
	activeShader->use();

	activeShader->setMat4("projView", camera->getProjView());
	activeShader->setMat4("model", glm::mat4(1));

	activeShader->setBool("material.shadow", false);
	activeShader->setBool("material.lighting", false);

	activeShader->setVec3("sun.direction", sun.getLight().direction);
	activeShader->setVec3("sun.color", sun.getLight().color);

	TextureManager::bindTexture(BlocksDatabase::getTextureAtlas(), *activeShader, "tex");
}

void ChunkRenderer::render(std::vector<ChunkMesh*>& meshes, Camera* camera, bool onlyVisible) {
	for (ChunkMesh* mesh : meshes) {
		if (!onlyVisible || camera->isAABBInFrustum(mesh->getModel().aabb))
			mesh->getModel().draw(activeShader);
	}
}

void ChunkRenderer::renderLights(const Sun& sun) {
	renderLights(solidMeshes, sun);
	renderLights(floraMeshes, sun);
}

void ChunkRenderer::renderLights(std::vector<ChunkMesh*>& meshes, const Sun& sun) {
	if (!meshes.size())
		return;

	activeShader = sun.getLight().getFramebuffer().getShader();

	render(meshes);
}