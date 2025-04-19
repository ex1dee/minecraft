#version 330 core

#define UNDEFINED_BONE_ID -1
#define MAX_BONE_INFLUENCE 4
#define MAX_BONES 20

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;
layout (location = 4) in vec4 boneWeights;
layout (location = 5) in ivec4 boneIDs;

out vec4 cameraSpacePos;
out vec4 Color;
out vec3 Normal;
out vec2 TexCoords;
out vec3 FragPos;

uniform bool useColors;
uniform bool useBones;

uniform mat4 boneMatrices[MAX_BONES];
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() { 
	vec4 finalPosition = vec4(0);
	vec3 finalNormal = vec3(0);

	if (useBones) {
		for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
			int boneID = boneIDs[i];

			if (boneID != UNDEFINED_BONE_ID && boneID < MAX_BONES) {
				finalPosition += boneWeights[i] * (boneMatrices[boneID] * vec4(aPos, 1));
				finalNormal += mat3(boneMatrices[boneID]) * aNormal;
			}
		}
	}

	if (length(finalPosition) == 0)
		finalPosition = vec4(aPos, 1);
	if (length(finalNormal) == 0)
		finalNormal = aNormal;

	cameraSpacePos = view * model * finalPosition;
	Color = useColors ? aColor : vec4(1);
	Normal = normalize(finalNormal);
	TexCoords = aTexCoords;
	FragPos = vec3(finalPosition);

	gl_Position = projection * cameraSpacePos;
}