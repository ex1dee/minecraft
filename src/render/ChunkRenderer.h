#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include <vector>

#include "../world/chunk/ChunkMesh.h"
#include "../player/Camera.h"
#include "../shaders/Shader.h"
#include "light/DirectLight.h"

class ChunkRenderer {
	std::vector<ChunkMesh*> solidMeshes;
	std::vector<ChunkMesh*> waterMeshes;
	Shader* defShader;

	void render(Camera& camera, std::vector<ChunkMesh*>& meshes);
	void updateSolidShader(Camera& camera, DirectLight* sunLight);
	void renderLights(std::vector<ChunkMesh*>& meshes, DirectLight* sunLight);
public:
	ChunkRenderer();
	~ChunkRenderer();

	void add(ChunkMeshCollection& chunk);
	void renderLights(DirectLight* sunLight);
	void render(Camera& camera, DirectLight* sunLight);
};

#endif