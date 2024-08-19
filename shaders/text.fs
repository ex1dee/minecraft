#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D tex;
uniform vec4 color;

void main() {
	vec4 sample = vec4(vec3(1), texture(tex, TexCoord).r);

	FragColor = color * sample;
}