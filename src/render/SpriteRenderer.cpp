#include "SpriteRenderer.h"

#include "Renderer.h"

void SpriteRenderer::render(const Sun& sun, const Camera& camera) {
	Renderer::startTransparentRender();
	updateShader(sun, camera);

	for (Sprite* sprite : sprites) {
		sprite->draw(*activeShader);
	}

	sprites.clear();

	Renderer::finishTransparentRender();
}

void SpriteRenderer::updateShader(const Sun& sun, const Camera& camera) {
	activeShader = &ShadersDatabase::get(ShaderType::SPRITE);
	activeShader->use();

	activeShader->setMat4("projection", camera.getProjection());
	activeShader->setMat4("view", camera.getView());

	activeShader->setBool("sunEnabled", true);
	activeShader->setVec3("sunDirection", sun.getLight().direction);
}

void SpriteRenderer::add(Sprite* sprite) {
	if (sprite->texture.data != nullptr)
		sprites.push_back(sprite);
}