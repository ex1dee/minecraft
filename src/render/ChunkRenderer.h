#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include <vector>

#include "../world/chunk/ChunkMesh.h"
#include "../shaders/Shader.h"
#include "../player/Camera.h"
#include "../world/Sun.h"
#include "light/DirectLight.h"

class ChunkRenderer {
	std::vector<ChunkMesh*> solidMeshes;
	std::vector<ChunkMesh*> waterMeshes;
	std::vector<ChunkMesh*> floraMeshes;
	Shader* activeShader;
	Shader* defShader;
	Shader* floraShader;

	void updateSolidShader(Camera* camera, const Sun& sun);
	void updateFloraShader(Camera* camera, const Sun& sun);
	void renderLights(std::vector<ChunkMesh*>& meshes, const Sun& sun);
	void render(std::vector<ChunkMesh*>& meshes, Camera* camera = nullptr, bool onlyVisible = false);
public:
	ChunkRenderer();
	~ChunkRenderer();

	void renderLights(const Sun& sun);
	void render(Camera* camera, const Sun& sun);
	void add(const ChunkMeshCollection& chunk);
};

#endif