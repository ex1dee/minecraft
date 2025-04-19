#include "EntityRenderer.h"

#include "../world/World.h"
#include "Renderer.h"

void EntityRenderer::add(std::shared_ptr<Entity>& entity) {
	if (entity->getModel() != nullptr && !entity->getModel()->isEmpty())
		entities.push_back(entity);
}

void EntityRenderer::render(const Camera& camera, const Sun& sun) {
	Renderer::startTransparentRender(true);

	updateShader(camera, sun);

	for (auto& entity : entities) {
		render(*entity, &camera, true);
	}

	entities.clear();

	Renderer::finishTransparentRender();
	activeShader->setBool("useBones", false);
	activeShader->setMat4("parentBoneMatrix", glm::mat4(1.0f));
}

void EntityRenderer::updateShader(const Camera& camera, const Sun& sun) {
	activeShader = &ShadersDatabase::get(ShaderType::DEFAULT);
	activeShader->use();

	activeShader->setMat4("projection", camera.getProjection());
	activeShader->setMat4("view", camera.getView());
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

void EntityRenderer::render(Entity& entity, const Camera* camera, bool onlyVisible) {
	if (camera == nullptr
	|| (onlyVisible && entity.getType().id == PLAYER && camera->getViewMode() == FIRST_PERSON)
	|| (entity.isInCameraSpace && camera->getViewMode() != FIRST_PERSON))
		return;

	if (entity.isInCameraSpace || (entity.isAtBufferedChunk() && (!onlyVisible || camera->isAABBInFrustum(entity.getModel()->aabb)))) {
		updateModelMatrix(entity);

		if (entity.isInCameraSpace) {
			activeShader->setMat4("view", glm::mat4(1.0f));
			Renderer::startTransparentRender(true);
		} else {
			activeShader->setMat4("view", camera->getView());
		}

		if (entity.hasAnimators()) {
			std::vector<glm::mat4> boneMatrices = entity.updateAnimators();
			
			for (int i = 0; i < boneMatrices.size(); ++i) {
				activeShader->setMat4(("boneMatrices[" + std::to_string(i) + "]").c_str(), boneMatrices[i]);
			}

			activeShader->setBool("useBones", true);
		} else {
			activeShader->setBool("useBones", false);
		}

		entity.getWorld()->getFogForEntity(entity).addToShader(activeShader);
		entity.getModel()->draw(*activeShader);

		TextureManager::unbindTexture(*activeShader, DEFAULT_TEXTURE_UNIFORM);
	}
}

void EntityRenderer::updateModelMatrix(const Entity& entity) {
	Transform transform = entity.transform;
	transform.add(entity.modelTransform);
	transform.rotation += glm::vec3(0, 180.0f - entity.orientation.getYaw(), 0);

	activeShader->setMat4("model", transform.calcModel());
}