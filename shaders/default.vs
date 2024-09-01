#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;

out vec4 cameraSpacePos;
out vec4 Color;
out vec3 Normal;
out vec2 TexCoords;
out vec3 FragPos;

uniform bool useColors;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	cameraSpacePos = view * model * vec4(aPos, 1);
	Color = useColors ? aColor : vec4(1);
	Normal = normalize(aNormal);
	TexCoords = aTexCoords;
	FragPos = aPos;

	gl_Position =  projection * cameraSpacePos;
}