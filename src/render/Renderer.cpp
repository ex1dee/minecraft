#include "Renderer.h"

#include "../world/WorldConstants.h"
#include "../world/chunk/Chunk.h"
#include "../world/World.h"
#include "../window/Window.h"

Renderer::Renderer(Player& player)
	: player(&player) {

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

	const Fog& fog = world.getFog();
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

	entityRenderer.render(camera, sun, fog);
	chunkRenderer.render(camera, sun, fog);

	disableCullFace();
	
	cloudsRenderer.render(clouds, sun, *player);
	blockFrameRenderer.render(*player);
	spriteRenderer.render(sun, camera);
	textRenderer.render(camera);
	guiRenderer.render();
}

void Renderer::addChunk(Chunk* chunk) {
	if (chunk == nullptr)
		return;
	
	chunkRenderer.add(chunk->getMeshes());
}

void Renderer::addEntity(Entity* entity) {
	if (entity == nullptr)
		return;

	entityRenderer.add(entity);
}

void Renderer::addSprite(Sprite* sprite) {
	if (sprite == nullptr)
		return;

	spriteRenderer.add(sprite);
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

void Renderer::startTransparentRender() {
	disableCullFace();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
}

void Renderer::finishTransparentRender() {
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	enableCullFace();
}