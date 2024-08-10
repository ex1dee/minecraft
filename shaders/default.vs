#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec4 cameraSpacePos;
out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	FragPos = aPos;
	Normal = normalize(aNormal);
	TexCoords = aTexCoords;
	cameraSpacePos = view * model * vec4(aPos, 1);

	gl_Position =  projection * cameraSpacePos;
}