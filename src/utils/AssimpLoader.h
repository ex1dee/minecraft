#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <vector>
#include <string>
#include <map>

#include "../animation/skeletal/Bone/BoneInfo.h"
#include "../render/model/Model.h"

class AssimpLoader {
	std::unique_ptr<Model> model = nullptr;
	std::string directory;
	bool flipTexture;

	std::map<std::string, BoneInfo> boneInfoMap;
	int boneCounter = 0;

	TextureType getTextureTypeBy(aiTextureType type);
	void addMesh(const aiScene* scene, const aiMesh* mesh);
	void addIndices(const aiMesh* mesh, MeshData& meshData);
	void addVertices(const aiMesh* mesh, MeshData& meshData);
	void processNode(const aiScene* scene, const aiNode* node);
	void addVertex(const aiMesh* mesh, MeshData& meshData, int i);
	void addMaterial(const aiScene* scene, const aiMesh* mesh, MeshData& meshData);
	void addBoneWeights(const aiScene* scene, const aiMesh* mesh, MeshData& meshData);
	void loadMaterialTextures(MeshData& meshData, aiMaterial* material, aiTextureType type);
public:
	AssimpLoader(const std::string& path, bool flipTexture = false);
	std::unique_ptr<Model> finish() { return std::move(model); }

	auto& getBoneInfoMap() { return boneInfoMap; }
	int& getBoneCount() { return boneCounter; }
};

#endif