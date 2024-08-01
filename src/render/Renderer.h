#ifndef RENDERER_H
#define RENDERER_H

#include "light/DirectLight.h"
#include "SkyboxRenderer.h"
#include "ChunkRenderer.h"
#include "RenderInfo.h"

class Chunk;

class Renderer {
	ChunkRenderer chunkRenderer;
	SkyboxRenderer skyboxRenderer;
	Shader* FBOShader;
public:
	Renderer();
	~Renderer();

	void setTime(float time, Player& player);
	void renderChunk(Chunk* chunk);
	void finishRender(Player& player, Camera& camera);

	static void drawElements(const RenderInfo& rInfo);
};

#endif