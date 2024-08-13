#version 330 core

#define MIN_SUN_LIGHT 0.1

out vec4 FragColor;
in vec2 TexCoord;

uniform vec3 sunDirection;
uniform sampler2D tex;

float calcSunLight();

void main() {
	float density = texture(tex, TexCoord).r;
	vec3 color = vec3(density);

	color = max(color, MIN_SUN_LIGHT);
	color = min(color, calcSunLight());

	FragColor = vec4(color, min(0.6, pow(density, 3.0)));
}

float calcSunLight() {
	float sunLight = clamp(0.3 - sunDirection.y, MIN_SUN_LIGHT, 1);

	return sunLight;
}