#ifndef RENDERER_H
#define RENDERER_H

#include "SkyboxRenderer.h"
#include "ChunkRenderer.h"
#include "RenderInfo.h"

class Chunk;

class Renderer {
	ChunkRenderer chunkRenderer;
	SkyboxRenderer skyboxRenderer;
public:
	Renderer() {}

	void setTime(float time);
	void renderChunk(Chunk* chunk);
	void finishRender(Player& player, Camera& camera);

	static void drawElements(RenderInfo rInfo);
};

#endif