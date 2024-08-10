#include "Renderer.h"

#include "../world/WorldConstants.h"
#include "../world/chunk/Chunk.h"
#include "../world/World.h"
#include "../window/Window.h"

void Renderer::finishRender(Player& player, Camera* camera, World& world) {
	glEnable(GL_DEPTH_TEST);
	
	Sun* sun = world.getSun();

	sun->getLight().startRender();
	chunkRenderer.renderLights(*sun);
	entityRenderer.renderLights(*sun);
	sun->getLight().finishRender();

	Window::setWindowViewport();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_MULTISAMPLE);
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);

	const Fog& fog = world.getFog(player);

	skyboxRenderer.render(camera, *sun, fog);

	if (!player.isFlying()) {
		enableCullFace();
	} else {
		disableCullFace();
	}

	glEnable(GL_MULTISAMPLE);
	glDepthMask(GL_TRUE);

	entityRenderer.render(camera, *sun, fog);
	chunkRenderer.render(camera, *sun, fog);

	disableCullFace();

	blockFrameRenderer.render(camera, player);
	guiRenderer.render();
}

void Renderer::addChunk(Chunk* chunk) {
	chunkRenderer.add(chunk->getMeshes());
}

void Renderer::addEntity(Entity* entity) {
	entityRenderer.add(entity);
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