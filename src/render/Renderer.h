#ifndef RENDERER_H
#define RENDERER_H

#include "../GL/GLHelper.h"

#include "light/DirectLight.h"

#include "BlockFrameRenderer.h"
#include "SkyboxRenderer.h"
#include "EntityRenderer.h"
#include "CloudsRenderer.h"
#include "ChunkRenderer.h"
#include "TextRenderer.h"
#include "GUIRenderer.h"

class Chunk;

class Renderer {
	BlockFrameRenderer blockFrameRenderer;
	SkyboxRenderer skyboxRenderer;
	EntityRenderer entityRenderer;
	SpriteRenderer spriteRenderer;
	CloudsRenderer cloudsRenderer;
	ChunkRenderer chunkRenderer;
	TextRenderer textRenderer;
	GUIRenderer guiRenderer;

	std::shared_ptr<Player> player;
public:
	Renderer(std::shared_ptr<Player>& player);

	void finishRender(World& world);

	void addText(std::shared_ptr<Text2D>& text);
	void addChunk(std::shared_ptr<Chunk>& chunk);
	void addSprite(std::shared_ptr<Sprite>& sprite);
	void addEntity(std::shared_ptr<Entity>& entity);
	
	static void enableCullFace();
	static void disableCullFace();
	static void finishTransparentRender();
	static void startTransparentRender(bool depthMask = false);
};

#endif