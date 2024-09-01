#include "AssimpLoader.h"

#include "../textures/TextureLoader.h"
#include "Files.h"

std::string AssimpLoader::directory;
std::unique_ptr<Model> AssimpLoader::model;

std::unique_ptr<Model> AssimpLoader::load(const std::string& path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "ERROR::ASSIMP\n" << importer.GetErrorString() << "\n";

		return nullptr;
	}

	directory = Files::getDirectory(path);
	model = std::make_unique<Model>();

	processNode(scene, scene->mRootNode);
	
	return std::move(model);
}

void AssimpLoader::processNode(const aiScene* scene, const aiNode* node) {
	for (int i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		addMesh(scene, mesh);
	}

	for (int i = 0; i < node->mNumChildren; ++i) {
		processNode(scene, node->mChildren[i]);
	}
}

void AssimpLoader::addMesh(const aiScene* scene, const aiMesh* mesh) {
	std::unique_ptr<MeshData> meshData = std::make_unique<MeshData>(MeshType::ASSIMP, 3);

	addVertices(mesh, *meshData);
	addIndices(mesh, *meshData);
	addMaterial(scene, mesh, *meshData);

	model->addMesh(meshData);
}

void AssimpLoader::addVertices(const aiMesh* mesh, MeshData& meshData) {
	for (int i = 0; i < mesh->mNumVertices; ++i) {
		addVertex(mesh, meshData, i);
	}
}

void AssimpLoader::addVertex(const aiMesh* mesh, MeshData& meshData, int i) {
	meshData.vertexPositions.push_back(mesh->mVertices[i].x);
	meshData.vertexPositions.push_back(mesh->mVertices[i].y);
	meshData.vertexPositions.push_back(mesh->mVertices[i].z);

	meshData.normals.push_back(mesh->mNormals[i].x);
	meshData.normals.push_back(mesh->mNormals[i].y);
	meshData.normals.push_back(mesh->mNormals[i].z);

	if (mesh->mTextureCoords[0]) {
		meshData.textureCoords.push_back(mesh->mTextureCoords[0][i].x);
		meshData.textureCoords.push_back(mesh->mTextureCoords[0][i].y);
	}
}

void AssimpLoader::addIndices(const aiMesh* mesh, MeshData& meshData) {
	for (int i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; ++j) {
			meshData.indices.push_back(face.mIndices[j]);
		}
	}
}

void AssimpLoader::addMaterial(const aiScene* scene, const aiMesh* mesh, MeshData& meshData) {
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		loadMaterialTextures(meshData, material, aiTextureType_DIFFUSE);
		loadMaterialTextures(meshData, material, aiTextureType_SPECULAR);
	}
}

void AssimpLoader::loadMaterialTextures(MeshData& meshData, aiMaterial* material, aiTextureType type) {
	for (int i = 0; i < material->GetTextureCount(type); ++i) {
		aiString texName;
		material->GetTexture(type, i, &texName);
		
		std::string path = Files::getFullPath(directory, texName.C_Str());
		meshData.textures.push_back(TextureLoader::loadBasic(path, true, getTextureTypeBy(type)));
	}
}

TextureType AssimpLoader::getTextureTypeBy(aiTextureType type) {
	if (type == aiTextureType_DIFFUSE)
		return TextureType::DIFFUSE;
	else if (type == aiTextureType_SPECULAR)
		return TextureType::SPECULAR;
}