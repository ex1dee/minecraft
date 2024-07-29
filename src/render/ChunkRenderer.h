#ifndef CHUNKRENDERER_H
#define CHUNKRENDERER_H

#include <vector>

#include "../world/chunk/ChunkMesh.h"
#include "../player/Camera.h"
#include "../shaders/Shader.h"

class ChunkRenderer {
	std::vector<ChunkMesh*> solidMeshes;
	std::vector<ChunkMesh*> waterMeshes;
	Shader* activeShader;
	Shader* defShader;

	void render(std::vector<ChunkMesh*>& mesh);
public:
	ChunkRenderer();
	~ChunkRenderer();

	void updateSolidShader(Camera& camera, const glm::vec3& lightDir);
	void add(ChunkMeshCollection& chunk);
	void render(Camera& camera, const glm::vec3& lightDir);
};

#endif