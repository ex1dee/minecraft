#include "Renderer.h"

#include <glad/glad.h>

#include "../world/chunk/Chunk.h"

Renderer::Renderer() {
	lightDir = glm::vec3(0, -1, 0);
}

void Renderer::renderChunk(Chunk* chunk) {
	chunkRenderer.add(chunk->getMeshes());
}

void Renderer::finishRender(Player& player, Camera& camera) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	skyboxRenderer.render(camera, lightDir);

	if (!player.isFlying()) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);
	} else {
		glDisable(GL_CULL_FACE);
	}

	chunkRenderer.render(camera, lightDir);
}

void Renderer::setTime(float time) {
	time = glm::radians(time);
	lightDir.x = -sin(time);
	lightDir.y = -cos(time);
}

void Renderer::drawElements(const RenderInfo& rInfo) {
	glBindVertexArray(rInfo.VAO);

	if (rInfo.indicesCount) {
		glDrawElements(GL_TRIANGLES, rInfo.indicesCount, GL_UNSIGNED_INT, 0);
	} else if (rInfo.vertexCount) {
		glDrawArrays(GL_TRIANGLES, 0, rInfo.vertexCount);
	}
}