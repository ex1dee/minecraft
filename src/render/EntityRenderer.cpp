#include "EntityRenderer.h"

void EntityRenderer::add(Entity* entity) {
	if (!entity->type->model->isEmpty())
		entities.push_back(entity);
}

void EntityRenderer::render(Camera* camera, const Sun& sun, const Fog& fog) {
	updateShader(camera, sun, fog);

	for (Entity* entity : entities) {
		//render(entity, camera, true);
	}

	entities.clear();
}

void EntityRenderer::updateShader(Camera* camera, const Sun& sun, const Fog& fog) {
	activeShader = ShadersDatabase::get(ShaderType::DEFAULT);
	activeShader->use();

	fog.addToShader(activeShader);

	activeShader->setMat4("projView", camera->getProjView());
	activeShader->setVec3("cameraPos", camera->getPosition());

	activeShader->setBool("material.shadow", false);
	activeShader->setBool("material.lighting", true);

	activeShader->setMat4("sun.shadow.projView", sun.getLight().getFramebuffer().getProjView());
	activeShader->setVec3("sun.direction", sun.getLight().direction);
	activeShader->setVec3("sun.color", sun.getLight().color);

	activeShader->setInt("pointLightCount", 0);
}

void EntityRenderer::renderLights(const Sun& sun) {
	activeShader = sun.getLight().getFramebuffer().getShader();

	for (Entity* entity : entities) {
		render(entity);
	}
}

void EntityRenderer::render(Entity* entity, Camera* camera, bool onlyVisible) {
	Model* model = entity->type->model;
	updateModelMatrix(entity);

	model->draw(activeShader);
}

void EntityRenderer::updateModelMatrix(Entity* entity) {
	glm::mat4 matModel(1.0f);
	
	matModel = entity->transform.calcModel();
	matModel *= entity->orientation.getRotation();
	matModel *= entity->type->offset.calcModel();

	activeShader->setMat4("model", matModel);
}