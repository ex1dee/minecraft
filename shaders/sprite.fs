#version 330 core

#define MIN_SUN_LIGHT 0.25

out vec4 FragColor;
in vec2 TexCoord;

uniform bool sunEnabled;
uniform vec3 sunDirection;

uniform sampler2D tex;
uniform vec4 color;

float calcSunLight();

void main() {
	FragColor = texture(tex, TexCoord) * color;
	
	if (sunEnabled) {
		FragColor = max(FragColor, MIN_SUN_LIGHT);
		FragColor = min(FragColor, calcSunLight());
	}
}

float calcSunLight() {
	float sunLight = clamp(0.3 - sunDirection.y, MIN_SUN_LIGHT, 1);

	return sunLight;
}