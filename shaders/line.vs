#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 FragPos;

uniform mat4 projView;

void main() {
	FragPos = aPos;

	gl_Position = projView * vec4(aPos, 1.0);
}