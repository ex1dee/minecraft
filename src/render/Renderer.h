#ifndef RENDERER_H
#define RENDERER_H

#include "SkyboxRenderer.h"
#include "ChunkRenderer.h"
#include "RenderInfo.h"

class Chunk;

class Renderer {
	ChunkRenderer chunkRenderer;
	SkyboxRenderer skyboxRenderer;
	glm::vec3 lightDir;
public:
	Renderer();

	void setTime(float time);
	void renderChunk(Chunk* chunk);
	void finishRender(Player& player, Camera& camera);

	static void drawElements(const RenderInfo& rInfo);
	static void drawPoints(const RenderInfo& rInfo);
};

#endif