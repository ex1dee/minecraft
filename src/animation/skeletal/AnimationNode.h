#ifndef ANIMATIONNODE_H
#define ANIMATIONNODE_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

class AnimationNode {
public:
	std::vector<AnimationNode> children;
	std::string boneName;
	glm::mat4 transform;

	AnimationNode() = default;

	AnimationNode(AnimationNode&& other) = default;
	AnimationNode& operator=(AnimationNode&& other) = default;

	AnimationNode(const AnimationNode& other) = default;
	AnimationNode& operator=(const AnimationNode& other) = default;
};

#endif