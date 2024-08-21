#include "CloudsRenderer.h"

#include "../render/Renderer.h"

void CloudsRenderer::render(const Clouds& clouds, const Sun& sun, const Player& player) {
	if (player.getLiquidAtEyes() != nullptr)
		return;

	updateShader(player.getCamera(), sun);
	Renderer::startTransparentRender();

	std::shared_ptr<Sprite> sprite = clouds.getSprite();

	if (sprite != nullptr)
		sprite->draw(*activeShader);

	Renderer::finishTransparentRender();
}

void CloudsRenderer::updateShader(const Camera& camera, const Sun& sun) {
	activeShader = &ShadersDatabase::get(ShaderType::CLOUDS);
	activeShader->use();

	activeShader->setMat4("projection", camera.getProjection());
	activeShader->setMat4("view", camera.getView());

	activeShader->setVec3("sunDirection", sun.getLight().direction);
}