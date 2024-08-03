#version 330 core

#define MIN_SUN_LIGHT 0.25
#define MAX_LIGHTS 16
#define MIN_SHADOW_BIAS 0.005
#define MAX_SHADOW_BIAS 0.0125

#define POINT_LIGHT_CONSTANT 1.0
#define POINT_LIGHT_LINEAR 1.0

struct LightShadow {
	mat4 projView;
	sampler2D depthMap;
};

struct PointLight {
	LightShadow shadow;
	vec3 position;
	vec3 color;

	float constant;
	float linear;
	float quadratic;
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

uniform DirectLight sun;

uniform int pointLightCount;
uniform PointLight pointLight[MAX_LIGHTS];

float calcShadow(LightShadow lightShadow, vec3 lightDir) {
	vec4 lightFragPos = lightShadow.projView * vec4(FragPos, 1);
	vec3 projCoords = lightFragPos.xyz / lightFragPos.w;
	projCoords = (projCoords + 1) * 0.5;

	if (projCoords.z > 1)
		return 1;

	float closestDepth = texture(lightShadow.depthMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	vec2 texelSize = 1 / textureSize(lightShadow.depthMap, 0);
	float bias = max(MIN_SHADOW_BIAS, MAX_SHADOW_BIAS * (1 - dot(vec3(0, -1, 0), lightDir)));
	float shadow = currentDepth - bias > closestDepth ? 0 : 1;

	//for (int x = -1; x <= 1; ++x) {
	//	for (int y = -1; y <= 1; ++y) {
	//		float pcfDepth = texture(lightShadow.depthMap, projCoords.xy + vec2(x, y) * texelSize).r;
	//		shadow += currentDepth - bias > pcfDepth ? 0 : 1;
	//	}
	//}

	//shadow /= 9;

	return shadow;
}

float calcSunLight() {
	float sunLight = clamp(0.15 - sun.direction.y, MIN_SUN_LIGHT, 1);

	return sunLight;
}

vec3 calcDiffuse(vec3 lightDir, vec3 lightColor, vec3 normal) {
	float diff = max(0.6, dot(normal, -lightDir));
	vec3 diffuse = diff * lightColor;

	return diffuse;
}

float calcAttenuation(PointLight light, float distance) {
	 return 1.0 / (light.constant + light.linear * distance + 
  			       light.quadratic * (distance * distance));
}

void main() {
	vec3 normal = normalize(Normal);
	vec3 result = vec3(0);
	float shadow = 1;

	float sunLight = calcSunLight();
	result += calcDiffuse(sun.direction, sun.color, normal);
	shadow = min(shadow, calcShadow(sun.shadow, sun.direction));

	for (int i = 0; i < pointLightCount; ++i) {
		//PointLight light = pointLight[i];
		//vec3 lightDir = normalize(light.position - FragPos);
		//float distance = length(light.position - FragPos);

		//result += calcDiffuse(lightDir, light.color, normal);
		//result *= calcAttenuation(light, distance);

		//shadow = min(shadow, calcShadow(light.shadow, lightDir));
	}

	vec3 lighting = shadow * result;
	lighting = max(lighting, MIN_SUN_LIGHT);
	lighting = min(lighting, sunLight);

	FragColor = vec4(lighting, 1) * texture(tex, TexCoord);
}