#version 330 core

#define MIN_SUN_LIGHT 0.25

out vec4 FragColor;
in vec3 FragPos;
in vec2 TexCoords;

struct DirectLight {
	vec3 direction;
	vec3 color;
};

uniform DirectLight sun;
uniform sampler2D tex;

float calcSunLight();

void main() {
	float sunLight = calcSunLight();
	vec3 lighting = vec3(sunLight);

	vec4 texColor = texture(tex, TexCoords);

	FragColor = vec4(lighting, 1) * texColor;
}

float calcSunLight() {
	float sunLight = clamp(0.15 - sun.direction.y, MIN_SUN_LIGHT, 1);

	return sunLight;
}