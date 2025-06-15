#include "Animation.h"

#include <iostream>

#include "../../utils/AssimpHelper.h"

Animation::Animation(const std::string& path, AssimpLoader& assimpLoader) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    
    if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP\n" << importer.GetErrorString() << "\n";
        return;
    }

    if (!scene->mAnimations) {
        std::cerr << "ERROR::ASSIMP\nThere are no animations in the scene " << path << "\n";
        return;
    }

    aiAnimation* animation = scene->mAnimations[0];
    ticksPerSecond = animation->mTicksPerSecond;
    duration = animation->mDuration;
    
    processNode(root, scene->mRootNode);
    readBones(animation, assimpLoader);
}

void Animation::processNode(AnimationNode& dest, const aiNode* src) {
    assert(src);

    dest.transform = AssimpHelper::getGLMMatrix(src->mTransformation);
    dest.boneName = src->mName.data;

    for (int i = 0; i < src->mNumChildren; ++i) {
        AnimationNode child;
        processNode(child, src->mChildren[i]);
        dest.children.push_back(child);
    }
}

void Animation::readBones(const aiAnimation* animation, AssimpLoader& assimpLoader) {
    auto& boneInfoMap = assimpLoader.getBoneInfoMap();
    int& boneCount = assimpLoader.getBoneCount();

    for (int i = 0; i < animation->mNumChannels; ++i) {
        aiNodeAnim* channel = animation->mChannels[i];
        const std::string& boneName = channel->mNodeName.data;
        
        bones.emplace(boneName, Bone(boneName, boneCount, channel));

        if (!boneInfoMap.contains(boneName)) {
            boneInfoMap.emplace(boneName, BoneInfo());
            boneCount++;
        }
    }

    this->boneInfoMap = boneInfoMap;
}