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

	void updateSolidShader(Camera& camera);
	void renderLights(std::vector<ChunkMesh*>& meshes);
	void render(Camera& camera, std::vector<ChunkMesh*>& meshes);
public:
	ChunkRenderer();
	~ChunkRenderer();

	void renderLights();
	void render(Camera& camera);
	void add(ChunkMeshCollection& chunk);
};

#endif