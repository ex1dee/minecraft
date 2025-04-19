#ifndef ASSIMPHELPER_H
#define ASSIMPHELPER_H

#include <assimp/scene.h>
#include <glm/glm.hpp>

class AssimpHelper {
public:
	static glm::vec3 getGLMVec3(const aiVector3D& aiVec) {
		return glm::vec3(aiVec.x, aiVec.y, aiVec.z);
	}

	static glm::quat getGLMQuat(const aiQuaternion& aiQuat) {
		return glm::quat(aiQuat.w, aiQuat.x, aiQuat.y, aiQuat.z);
	}

	static glm::mat4 getGLMMatrix(const aiMatrix4x4& aiMat) {
		glm::mat4 mat;

		mat[0][0] = aiMat.a1; mat[1][0] = aiMat.a2; mat[2][0] = aiMat.a3; mat[3][0] = aiMat.a4;
		mat[0][1] = aiMat.b1; mat[1][1] = aiMat.b2; mat[2][1] = aiMat.b3; mat[3][1] = aiMat.b4;
		mat[0][2] = aiMat.c1; mat[1][2] = aiMat.c2; mat[2][2] = aiMat.c3; mat[3][2] = aiMat.c4;
		mat[0][3] = aiMat.d1; mat[1][3] = aiMat.d2; mat[2][3] = aiMat.d3; mat[3][3] = aiMat.d4;

		return mat;
	}
};

#endif