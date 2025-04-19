#ifndef BONE_H
#define BONE_H

#include <vector>
#include <string>

#include "key/KeyPosition.h"
#include "key/KeyRotation.h"
#include "key/KeyScale.h"

#include "../../../utils/AssimpHelper.h"
#include "../../AnimationConstants.h"

class Bone {
	std::vector<KeyPosition> positions;
	std::vector<KeyRotation> rotations;
	std::vector<KeyScale> scales;

	glm::mat4 localTransform;
	std::string name;
	int id;

	void readPositionKeys(const aiNodeAnim* nodeAnim);
	void readRotationKeys(const aiNodeAnim* nodeAnim);
	void readScaleKeys(const aiNodeAnim* nodeAnim);

	float getErpFactor(float lastTimeStamp, float nextTimeStamp, float time) const;
	glm::mat4 interpolatePosition(float time) const;
	glm::mat4 interpolateRotation(float time) const;
	glm::mat4 interpolateScale(float time) const;
public:
	Bone() {}
	Bone(const std::string& name, int id, const aiNodeAnim* nodeAnim);

	void update(float time);

	glm::mat4 getLocalTransform() { return localTransform; }
	std::string getName() const { return name; }
	int getID() { return id; }

	template<typename T>
	int getKeyIndex(float time, const std::vector<T>& keys) const {
		for (int i = 0; i < keys.size() - 1; ++i) {
			if (time <= keys[i + 1].timeStamp) {
				return i;
			}
		}

		return keys.size() - 1;
	}
};

#endif