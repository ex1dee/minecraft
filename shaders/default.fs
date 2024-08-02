#version 330 core

#define SUN_INDEX 0
#define MIN_SUN_LIGHT 0.15
#define MAX_LIGHTS 16
#define MIN_SHADOW_BIAS 0.005
#define MAX_SHADOW_BIAS 0.05

struct LightShadow {
	mat4 projView;
	sampler2D depthMap;
};

struct DirectLight {
	LightShadow shadow;
	vec3 direction;
	vec3 color;
};

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D tex;

uniform int directLightCount;
uniform DirectLight directLight[MAX_LIGHTS];

float calcDirectShadow(DirectLight light) {
	vec4 lightFragPos = light.shadow.projView * vec4(FragPos, 1);
	vec3 projCoords = lightFragPos.xyz / lightFragPos.w;
	projCoords = (projCoords + 1) * 0.5;

	if (projCoords.z > 1)
		return 1;

	float closestDepth = texture(light.shadow.depthMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	vec2 texelSize = 1 / textureSize(light.shadow.depthMap, 0);
	float bias = max(MIN_SHADOW_BIAS, MAX_SHADOW_BIAS * (1 - dot(vec3(0, -1, 0), light.direction)));
	float shadow = currentDepth - bias > closestDepth ? 0 : 1;

	//for (int x = -1; x <= 1; ++x) {
	//	for (int y = -1; y <= 1; ++y) {
	//		float pcfDepth = texture(light.shadow.depthMap, projCoords.xy + vec2(x, y) * texelSize).r;
	//		shadow += currentDepth - bias > pcfDepth ? 0 : 1;
	//	}
	//}

	//shadow /= 9;

	return shadow;
}

float calcSunLight() {
	vec3 sunLightDir = directLight[SUN_INDEX].direction;
	float sunLight = clamp(0.5 - sunLightDir.y, MIN_SUN_LIGHT, 1);

	return sunLight;
}

vec3 calcDirectLight(DirectLight light, vec3 normal) {
	float diff = max(0.5, dot(normal, -light.direction));
	vec3 diffuse = diff * light.color;

	return diffuse;
}

void main() {
	vec3 normal = normalize(Normal);
	vec3 result = vec3(0);
	float shadow = 1;
	
	for (int i = 0; i < directLightCount; ++i) {
		result += calcDirectLight(directLight[i], normal);
		shadow = min(shadow, calcDirectShadow(directLight[i]));
	}

	float sunLight = calcSunLight();

	vec3 lighting = shadow * result;
	lighting = max(lighting, MIN_SUN_LIGHT);
	lighting = min(lighting, sunLight);

	FragColor = vec4(lighting, 1) * texture(tex, TexCoord);
}