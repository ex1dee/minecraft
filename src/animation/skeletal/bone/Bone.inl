#include "Bone.h"

template<typename T>
int Bone::getKeyIndex(float time, const std::vector<T>& keys) const {
	for (int i = 0; i < keys.size() - 1; ++i) {
		if (time <= keys[i + 1].timeStamp) {
			return i;
		}
	}

	return keys.size() - 1;
}