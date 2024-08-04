#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include "light/DirectLight.h"
#include "SkyboxRenderer.h"
#include "EntityRenderer.h"
#include "ChunkRenderer.h"

class Chunk;

class Renderer {
	ChunkRenderer chunkRenderer;
	SkyboxRenderer skyboxRenderer;
	EntityRenderer entityRenderer;
	Shader* FBOShader;
public:
	void addChunk(Chunk* chunk);
	void addEntity(Entity* entity);
	void finishRender(Player& player, Camera* camera, World& world);
	
	static void startTransparentRender();
	static void finishTransparentRender();
};

#endif