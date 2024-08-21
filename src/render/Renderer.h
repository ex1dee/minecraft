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

	void addText(Text2D& text);
	void addChunk(Chunk& chunk);
	void addSprite(Sprite& sprite);
	void addEntity(Entity& entity);
	
	static void enableCullFace();
	static void disableCullFace();
	static void startTransparentRender();
	static void finishTransparentRender();
};

#endif