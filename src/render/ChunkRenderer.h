#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include <vector>

#include "../world/chunk/ChunkModel.h"
#include "../shaders/Shader.h"
#include "../player/Camera.h"
#include "../world/Sun.h"
#include "fog/Fog.h"

class ChunkRenderer {
	std::vector<std::shared_ptr<ChunkModel>> solidModel;
	std::vector<std::shared_ptr<ChunkModel>> liquidModel;
	std::vector<std::shared_ptr<ChunkModel>> floraModel;
	Shader* activeShader;

	void updateSolidShader();
	void updateFloraShader();
	void updateWaterShader();
	void updateDefaultShader(const Camera& camera, const Sun& sun, const Fog& fog);
	void renderLights(std::vector<std::shared_ptr<ChunkModel>>& model, const Sun& sun);
	void render(std::vector<std::shared_ptr<ChunkModel>>& model, const Camera* camera = nullptr, bool onlyVisible = false);
public:
	void renderLights(const Sun& sun);
	void render(const Camera& camera, const Sun& sun, const Fog& fog);
	void add(const ChunkModelCollection& chunk);
};

#endif