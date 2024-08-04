#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

#include "../render/model/Model.h"

class AssimpLoader {
	std::vector<Mesh*> meshes;
	std::string directory;
	Model* model;

	TextureType getTextureTypeBy(aiTextureType type);
	void addVertices(const aiMesh* mesh, MeshData& meshData);
	void addIndices(const aiMesh* mesh, MeshData& meshData);
	void addMaterial(const aiScene* scene, const aiMesh* mesh, MeshData& meshData);
	void addVertex(const aiMesh* mesh, MeshData& meshData, int i);
	void addMesh(const aiScene* scene, const aiMesh* mesh);
	void processNode(const aiScene* scene, const aiNode* node);
	void loadMaterialTextures(MeshData& meshData, aiMaterial* material, aiTextureType type);
public:
	Model* load(const std::string& path);
};

#endif