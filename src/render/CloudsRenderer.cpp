#include "CloudsRenderer.h"

#include "../render/Renderer.h"

void CloudsRenderer::render(Camera* camera, const Clouds& clouds, const Sun& sun, const Player& player) {
	if (player.isEyesInWater())
		return;

	updateShader(camera, sun);
	Renderer::startTransparentRender();

	Sprite* sprite = clouds.getSprite();

	if (sprite != nullptr)
		sprite->draw(activeShader);

	Renderer::finishTransparentRender();
}

void CloudsRenderer::updateShader(Camera* camera, const Sun& sun) {
	activeShader = ShadersDatabase::get(ShaderType::CLOUDS);
	activeShader->use();

	activeShader->setMat4("projection", camera->getProjection());
	activeShader->setMat4("view", camera->getView());

	activeShader->setVec3("sunDirection", sun.getLight().direction);
}