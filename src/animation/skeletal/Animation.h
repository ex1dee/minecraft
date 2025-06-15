#ifndef ANIMATION_H
#define ANIMATION_H

#include "../../utils/AssimpLoader.h"
#include "AnimationNode.h"
#include "Bone/Bone.h"

class Animation {
	std::unordered_map<std::string, BoneInfo> boneInfoMap;
	std::unordered_map<std::string, Bone> bones;
	AnimationNode root;
	double ticksPerSecond;
	double duration;

	void readBones(const aiAnimation* animation, AssimpLoader& assimpLoader);
	void processNode(AnimationNode& dest, const aiNode* src);
public:
	Animation(const std::string& path, AssimpLoader& assimpLoader);

	bool containsBone(const std::string& name) const { return bones.contains(name); }
	Bone* getBone(const std::string& name) { return bones.contains(name) ? &bones[name] : nullptr; }

	AnimationNode& getRoot() { return root; }
	auto& getBoneInfoMap() { return boneInfoMap; }
	float getTicksPerSecond() const { return ticksPerSecond; }
	float getDuration() const { return duration; }
};

#endif