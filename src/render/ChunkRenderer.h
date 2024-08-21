#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include <vector>

#include "../world/chunk/ChunkMesh.h"
#include "../shaders/Shader.h"
#include "../player/Camera.h"
#include "../world/Sun.h"
#include "fog/Fog.h"

class ChunkRenderer {
	std::vector<std::shared_ptr<ChunkMesh>> solidMeshes;
	std::vector<std::shared_ptr<ChunkMesh>> liquidMeshes;
	std::vector<std::shared_ptr<ChunkMesh>> floraMeshes;
	Shader* activeShader;

	void updateSolidShader();
	void updateFloraShader();
	void updateWaterShader();
	void updateDefaultShader(const Camera& camera, const Sun& sun, const Fog& fog);
	void renderLights(std::vector<std::shared_ptr<ChunkMesh>>& meshes, const Sun& sun);
	void render(std::vector<std::shared_ptr<ChunkMesh>>& meshes, const Camera* camera = nullptr, bool onlyVisible = false);
public:
	void renderLights(const Sun& sun);
	void render(const Camera& camera, const Sun& sun, const Fog& fog);
	void add(const ChunkMeshCollection& chunk);
};

#endif