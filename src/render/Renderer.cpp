#include "Renderer.h"

#include "../world/WorldConstants.h"
#include "../world/chunk/Chunk.h"
#include "../world/World.h"
#include "../window/Window.h"

Renderer::Renderer(std::shared_ptr<Player>& player)
	: player(player) {

}

void Renderer::finishRender(World& world) {
	glEnable(GL_DEPTH_TEST);
	
	const Sun& sun = world.getSun();

	sun.getLight().startRender();
	chunkRenderer.renderLights(sun);
	entityRenderer.renderLights(sun);
	sun.getLight().finishRender();

	Window::setWindowViewport();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_MULTISAMPLE);
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);

	const Fog& fog = world.getFogForEntity(*player);
	const Clouds& clouds = world.getClouds();
	Camera& camera = player->getCamera();

	skyboxRenderer.render(camera, sun, fog);

	if (!player->isFlying()) {
		enableCullFace();
	} else {
		disableCullFace();
	}

	glEnable(GL_MULTISAMPLE);
	glDepthMask(GL_TRUE);

	chunkRenderer.render(camera, sun, fog);

	disableCullFace();
	
	cloudsRenderer.render(clouds, sun, *player);
	entityRenderer.render(camera, sun);
	blockFrameRenderer.render(*player);
	spriteRenderer.render(sun, camera);
	textRenderer.render(camera);
	guiRenderer.render();
}

void Renderer::addChunk(std::shared_ptr<Chunk>& chunk) {
	chunkRenderer.add(chunk->getModel());
}

void Renderer::addEntity(std::shared_ptr<Entity>& entity) {
	entityRenderer.add(entity);
}

void Renderer::addSprite(std::shared_ptr<Sprite>& sprite) {
	spriteRenderer.add(sprite);
}

void Renderer::addText(std::shared_ptr<Text2D>& text) {
	textRenderer.add(text);
}

void Renderer::enableCullFace() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
}

void Renderer::disableCullFace() {
	glDisable(GL_CULL_FACE);
	glCullFace(GL_FRONT_AND_BACK);
}

void Renderer::startTransparentRender(bool depthMask) {
	disableCullFace();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(depthMask);
}

void Renderer::finishTransparentRender() {
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	enableCullFace();
}