#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include "light/DirectLight.h"

#include "BlockFrameRenderer.h"
#include "SkyboxRenderer.h"
#include "EntityRenderer.h"
#include "CloudsRenderer.h"
#include "ChunkRenderer.h"
#include "GUIRenderer.h"

class Chunk;

class Renderer {
	BlockFrameRenderer blockFrameRenderer;
	SkyboxRenderer skyboxRenderer;
	EntityRenderer entityRenderer;
	SpriteRenderer spriteRenderer;
	CloudsRenderer cloudsRenderer;
	ChunkRenderer chunkRenderer;
	GUIRenderer guiRenderer;
	Shader* FBOShader;
public:
	void addSprite(Sprite* sprite);
	void addChunk(Chunk* chunk);
	void addEntity(Entity* entity);
	void finishRender(Player& player, Camera* camera, World& world);
	
	static void enableCullFace();
	static void disableCullFace();
	static void startTransparentRender();
	static void finishTransparentRender();
};

#endif