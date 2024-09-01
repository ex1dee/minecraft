#include "ChunkRenderer.h"

#include "../textures/TextureManager.h"
#include "../world/block/BlocksDatabase.h"
#include "../shaders/ShadersDatabase.h"
#include "Renderer.h"

void ChunkRenderer::add(const ChunkModelCollection& chunk) {
	if (!chunk.solid->getModel().isEmpty())
		solidModel.push_back(chunk.solid);

	if (!chunk.liquid->getModel().isEmpty())
		liquidModel.push_back(chunk.liquid);

	if (!chunk.flora->getModel().isEmpty())
		floraModel.push_back(chunk.flora);
}

void ChunkRenderer::render(const Camera& camera, const Sun& sun, const Fog& fog) {
	updateDefaultShader(camera, sun, fog);

	if (solidModel.size()) {
		updateSolidShader();
		render(solidModel, &camera, true);

		solidModel.clear();
	}

	Renderer::startTransparentRender();

	if (floraModel.size()) {
		updateFloraShader();
		render(floraModel, &camera, true);

		floraModel.clear();
	}
	
	if (liquidModel.size()) {
		updateWaterShader();
		render(liquidModel, &camera, true);

		liquidModel.clear();
	}

	Renderer::finishTransparentRender();
}

void ChunkRenderer::updateDefaultShader(const Camera& camera, const Sun& sun, const Fog& fog) {
	activeShader = &ShadersDatabase::get(ShaderType::DEFAULT);
	activeShader->use();

	fog.addToShader(activeShader);

	activeShader->setVec3("cameraPos", camera.getPosition());
	activeShader->setMat4("projection", camera.getProjection());
	activeShader->setMat4("view", camera.getView());
	activeShader->setMat4("model", glm::mat4(1));

	activeShader->setMat4("sun.shadow.projView", sun.getLight().getFramebuffer().getProjView());
	activeShader->setVec3("sun.direction", sun.getLight().direction);
	activeShader->setVec3("sun.color", sun.getLight().color);

	activeShader->setInt("pointLightCount", 0);

	TextureManager::bindTexture(*BlocksDatabase::getTextureAtlas(), *activeShader, DEFAULT_TEXTURE_UNIFORM);
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
	renderLights(solidModel, sun);
	renderLights(floraModel, sun);
}

void ChunkRenderer::renderLights(std::vector<std::shared_ptr<ChunkModel>>& model, const Sun& sun) {
	if (!model.size())
		return;

	activeShader = &sun.getLight().getFramebuffer().getShader();

	render(model);
}

void ChunkRenderer::render(std::vector<std::shared_ptr<ChunkModel>>& model, const Camera* camera, bool onlyVisible) {
	for (auto& mesh : model) {
		if (!onlyVisible || camera->isAABBInFrustum(mesh->getModel().aabb))
			mesh->getModel().draw(*activeShader);
	}
}