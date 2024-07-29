#version 330 core

out vec4 FragColor;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D tex;
uniform vec3 lightDir;

void main() {
	float sunDt = clamp(0.5 - lightDir.y, 0.2, 1);
	vec3 sunLight = vec3(sunDt);

	FragColor = vec4(sunLight, 1) * texture(tex, TexCoord);
}