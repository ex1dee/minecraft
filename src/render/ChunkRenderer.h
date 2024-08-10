#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include <vector>

#include "../world/chunk/ChunkMesh.h"
#include "../shaders/Shader.h"
#include "../player/Camera.h"
#include "../world/Sun.h"

class ChunkRenderer {
	std::vector<ChunkMesh*> solidMeshes;
	std::vector<ChunkMesh*> waterMeshes;
	std::vector<ChunkMesh*> floraMeshes;
	Shader* activeShader;

	void updateSolidShader();
	void updateFloraShader();
	void updateWaterShader();
	void updateDefaultShader(Camera* camera, const Sun& sun);
	void renderLights(std::vector<ChunkMesh*>& meshes, const Sun& sun);
	void render(std::vector<ChunkMesh*>& meshes, Camera* camera = nullptr, bool onlyVisible = false);
public:
	void renderLights(const Sun& sun);
	void render(Camera* camera, const Sun& sun);
	void add(const ChunkMeshCollection& chunk);
};

#endif