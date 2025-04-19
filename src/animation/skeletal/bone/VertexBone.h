#ifndef VERTEXBONE_H
#define VERTEXBONE_H

#include <glm/glm.hpp>

class VertexBone {
public:
	int boneIDs[MAX_BONE_INFLUENCE];
	float boneWeights[MAX_BONE_INFLUENCE];

	VertexBone() {
		for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
			boneIDs[i] = UNDEFINED_BONE_ID;
			boneWeights[i] = 0.0f;
		}
	}
};

#endif