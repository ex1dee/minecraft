#include "Bone.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Bone::Bone(const std::string& name, int id, const aiNodeAnim* nodeAnim)
	: name(name), id(id), localTransform(1.0f) {
	readPositionKeys(nodeAnim);
	readRotationKeys(nodeAnim);
	readScaleKeys(nodeAnim);
}

void Bone::update(float time) {
	localTransform = interpolatePosition(time) * interpolateRotation(time) * interpolateScale(time);
}

glm::mat4 Bone::interpolatePosition(float time) const {
	if (positions.size() == 1)
		return glm::translate(glm::mat4(1.0f), positions[0].position);
	
	int curPoint = getKeyIndex(time, positions);
	float erpFactor = getErpFactor(positions[curPoint].timeStamp, positions[curPoint + 1].timeStamp, time);

	return glm::translate(
		glm::mat4(1.0f), 
		glm::mix(positions[curPoint].position, positions[curPoint + 1].position, erpFactor)
	);
}

glm::mat4 Bone::interpolateRotation(float time) const {
	if (rotations.size() == 1)
		return glm::toMat4(glm::normalize(rotations[0].rotation));

	int curPoint = getKeyIndex(time, rotations);
	float erpFactor = getErpFactor(rotations[curPoint].timeStamp, rotations[curPoint + 1].timeStamp, time);

	return glm::toMat4(glm::normalize(
		glm::slerp(rotations[curPoint].rotation, rotations[curPoint + 1].rotation, erpFactor)
	));
}

glm::mat4 Bone::interpolateScale(float time) const {
	if (scales.size() == 1)
		return glm::scale(glm::mat4(1.0f), scales[0].scale);

	int curPoint = getKeyIndex(time, scales);
	float erpFactor = getErpFactor(scales[curPoint].timeStamp, scales[curPoint + 1].timeStamp, time);
	
	return glm::scale(
		glm::mat4(1.0f),
		glm::mix(scales[curPoint].scale, scales[curPoint + 1].scale, erpFactor)
	);
}

float Bone::getErpFactor(float lastTimeStamp, float nextTimeStamp, float time) const {
	return (time - lastTimeStamp) / (nextTimeStamp - lastTimeStamp);
}

void Bone::readPositionKeys(const aiNodeAnim* nodeAnim) {
	for (int i = 0; i < nodeAnim->mNumPositionKeys; ++i) {
		KeyPosition data;
		data.position = AssimpHelper::getGLMVec3(nodeAnim->mPositionKeys[i].mValue);
		data.timeStamp = nodeAnim->mPositionKeys[i].mTime;
		positions.push_back(data);
	}
}

void Bone::readRotationKeys(const aiNodeAnim* nodeAnim) {
	for (int i = 0; i < nodeAnim->mNumRotationKeys; ++i) {
		KeyRotation data;
		data.rotation = AssimpHelper::getGLMQuat(nodeAnim->mRotationKeys[i].mValue);
		data.timeStamp = nodeAnim->mRotationKeys[i].mTime;
		rotations.push_back(data);
	}
}

void Bone::readScaleKeys(const aiNodeAnim* nodeAnim) {
	for (int i = 0; i < nodeAnim->mNumScalingKeys; ++i) {
		KeyScale data;
		data.scale = AssimpHelper::getGLMVec3(nodeAnim->mScalingKeys[i].mValue);
		data.timeStamp = nodeAnim->mScalingKeys[i].mTime;
		scales.push_back(data);
	}
}