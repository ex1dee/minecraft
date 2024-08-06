#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include "light/DirectLight.h"

#include "BlockFrameRenderer.h"
#include "SkyboxRenderer.h"
#include "EntityRenderer.h"
#include "ChunkRenderer.h"

class Chunk;

class Renderer {
	BlockFrameRenderer blockFrameRenderer;
	SkyboxRenderer skyboxRenderer;
	EntityRenderer entityRenderer;
	ChunkRenderer chunkRenderer;
	Shader* FBOShader;
public:
	void addChunk(Chunk* chunk);
	void addEntity(Entity* entity);
	void finishRender(Player& player, Camera* camera, World& world);
	
	static void enableCullFace();
	static void disableCullFace();
	static void startTransparentRender();
	static void finishTransparentRender();
};

#endif