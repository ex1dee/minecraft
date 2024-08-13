#include "ChunkRenderer.h"

#include "../textures/TextureManager.h"
#include "../world/block/BlocksDatabase.h"
#include "../shaders/ShadersDatabase.h"
#include "Renderer.h"

void ChunkRenderer::add(const ChunkMeshCollection& chunk) {
	if (!chunk.solid->getModel().isEmpty())
		solidMeshes.push_back(chunk.solid);

	if (!chunk.liquid->getModel().isEmpty())
		liquidMeshes.push_back(chunk.liquid);

	if (!chunk.flora->getModel().isEmpty())
		floraMeshes.push_back(chunk.flora);
}

void ChunkRenderer::render(Camera* camera, const Sun& sun, const Fog& fog) {
	updateDefaultShader(camera, sun, fog);

	if (solidMeshes.size()) {
		updateSolidShader();
		render(solidMeshes, camera, true);

		solidMeshes.clear();
	}

	Renderer::startTransparentRender();

	if (floraMeshes.size()) {
		updateFloraShader();
		render(floraMeshes, camera, true);

		floraMeshes.clear();
	}
	
	if (liquidMeshes.size()) {
		updateWaterShader();
		render(liquidMeshes, camera, true);

		liquidMeshes.clear();
	}

	Renderer::finishTransparentRender();
}

void ChunkRenderer::updateDefaultShader(Camera* camera, const Sun& sun, const Fog& fog) {
	activeShader = ShadersDatabase::get(ShaderType::DEFAULT);
	activeShader->use();

	fog.addToShader(activeShader);

	activeShader->setBool("water", false);

	activeShader->setVec3("cameraPos", camera->getPosition());
	activeShader->setMat4("projection", camera->getProjection());
	activeShader->setMat4("view", camera->getView());
	activeShader->setMat4("model", glm::mat4(1));

	activeShader->setMat4("sun.shadow.projView", sun.getLight().getFramebuffer().getProjView());
	activeShader->setVec3("sun.direction", sun.getLight().direction);
	activeShader->setVec3("sun.color", sun.getLight().color);

	activeShader->setInt("pointLightCount", 0);

	TextureManager::bindTexture(BlocksDatabase::getTextureAtlas(), *activeShader, "tex");
	TextureManager::bindDepthMap(sun.getLight().getFramebuffer().getDepthMap(), *activeShader, "sun.shadow.depthMap");
}

void ChunkRenderer::updateSolidShader() {
	activeShader->setBool("material.shadow", true);
	activeShader->setBool("material.lighting", true);
}

void ChunkRenderer::updateFloraShader() {
	activeShader->setBool("material.shadow", false);
	activeShader->setBool("material.lighting", false);
}

void ChunkRenderer::updateWaterShader() {
	activeShader->setBool("material.shadow", false);
	activeShader->setBool("material.lighting", false);
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

void ChunkRenderer::render(std::vector<ChunkMesh*>& meshes, Camera* camera, bool onlyVisible) {
	for (ChunkMesh* mesh : meshes) {
		if (!onlyVisible || camera->isAABBInFrustum(mesh->getModel().aabb))
			mesh->getModel().draw(activeShader);
	}
}