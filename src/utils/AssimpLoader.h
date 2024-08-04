#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

#include "../render/model/Model.h"

class AssimpLoader {
	static std::string directory;
	static Model* model;

	static TextureType getTextureTypeBy(aiTextureType type);
	static void addVertices(const aiMesh* mesh, MeshData& meshData);
	static void addIndices(const aiMesh* mesh, MeshData& meshData);
	static void addMaterial(const aiScene* scene, const aiMesh* mesh, MeshData& meshData);
	static void addVertex(const aiMesh* mesh, MeshData& meshData, int i);
	static void addMesh(const aiScene* scene, const aiMesh* mesh);
	static void processNode(const aiScene* scene, const aiNode* node);
	static void loadMaterialTextures(MeshData& meshData, aiMaterial* material, aiTextureType type);
public:
	static Model* load(const std::string& path);
};

#endif