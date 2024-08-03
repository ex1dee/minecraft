#include "Renderer.h"

#include <glad/glad.h>

#include "../world/WorldConstants.h"
#include "../world/chunk/Chunk.h"
#include "../world/World.h"
#include "../window/Window.h"

void Renderer::finishRender(Player& player, Camera* camera, World& world) {
	chunkRenderer.renderLights(world.getSun());

	Window::setWindowViewport();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	skyboxRenderer.render(camera, world.getSun());

	if (!player.isFlying()) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);
	} else {
		glDisable(GL_CULL_FACE);
	}

	chunkRenderer.render(camera, world.getSun());
}

void Renderer::renderChunk(Chunk* chunk) {
	chunkRenderer.add(chunk->getMeshes());
}

void Renderer::drawElements(const RenderInfo& rInfo) {
	glBindVertexArray(rInfo.VAO);

	if (rInfo.indicesCount) {
		glDrawElements(GL_TRIANGLES, rInfo.indicesCount, GL_UNSIGNED_INT, 0);
	} else if (rInfo.vertexCount) {
		glDrawArrays(GL_TRIANGLES, 0, rInfo.vertexCount);
	}
}