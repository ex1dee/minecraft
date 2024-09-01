#include "EntityRenderer.h"

#include "Renderer.h"

void EntityRenderer::add(std::shared_ptr<Entity>& entity) {
	if (entity->model != nullptr && !entity->model->isEmpty())
		entities.push_back(entity);
}

void EntityRenderer::render(const Camera& camera, const Sun& sun, const Fog& fog) {
	Renderer::startTransparentRender(true);

	updateShader(camera, sun, fog);

	for (auto& entity : entities) {
		render(*entity, &camera, true);
	}

	entities.clear();

	Renderer::finishTransparentRender();
}

void EntityRenderer::updateShader(const Camera& camera, const Sun& sun, const Fog& fog) {
	activeShader = &ShadersDatabase::get(ShaderType::DEFAULT);
	activeShader->use();

	fog.addToShader(activeShader);

	activeShader->setMat4("projView", camera.getProjView());
	activeShader->setVec3("cameraPos", camera.getPosition());

	activeShader->setBool("material.shadow", false);
	activeShader->setBool("material.lighting", true);

	activeShader->setMat4("sun.shadow.projView", sun.getLight().getFramebuffer().getProjView());
	activeShader->setVec3("sun.direction", sun.getLight().direction);
	activeShader->setVec3("sun.color", sun.getLight().color);

	activeShader->setInt("pointLightCount", 0);
}

void EntityRenderer::renderLights(const Sun& sun) {
	activeShader = &sun.getLight().getFramebuffer().getShader();

	for (auto& entity : entities) {
		render(*entity);
	}
}

void EntityRenderer::render(const Entity& entity, const Camera* camera, bool onlyVisible) {
	if (entity.getType().id == PLAYER) // TODO: delete this line
		return;

	updateModelMatrix(entity);

	// TODO: only visible
	entity.model->draw(*activeShader);
}

void EntityRenderer::updateModelMatrix(const Entity& entity) {
	Transform transform = entity.transform;
	transform.add(entity.modelTransform);

	//matModel *= entity.orientation.getRotation();

	activeShader->setMat4("model", transform.calcModel());
}