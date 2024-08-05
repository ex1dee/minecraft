#version 330 core

#define SHADOW_INTERPOLATION false

#define MIN_SUN_LIGHT 0.25
#define MIN_SUN_DIFFUSE 0.4
#define MIN_SHADOW_BIAS 0.005
#define MAX_SHADOW_BIAS 0.008
#define MAX_LIGHTS 16

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

struct Material {
	int diffuseCount;
	sampler2D diffuse[16];

	int specularCount;
	sampler2D specular[16];

	float shininess;

	bool shadow;
	bool lighting;
};

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform DirectLight sun;
uniform Material material;
uniform vec3 cameraPos;
uniform sampler2D tex;

uniform int pointLightCount;
uniform PointLight pointLight[MAX_LIGHTS];

float calcShadow(LightShadow lightShadow, vec3 lightDir);
float calcAttenuation(PointLight light, float distance);
vec3 calcPointLight (PointLight light);
vec3 calcSunDiffuse(DirectLight sun);
float calcSunLight();

vec3 result = vec3(0);

void main() {
	float shadow = 1;

	float sunLight = calcSunLight();
	result += calcSunDiffuse(sun);

	if (material.shadow)
		shadow = min(shadow, calcShadow(sun.shadow, sun.direction));

	if (material.lighting) {
		for (int i = 0; i < pointLightCount; ++i) {
			//PointLight light = pointLight[i];

			//result += calcPointLight(light);
			//shadow = min(shadow, calcShadow(light.shadow, lightDir));
		}
	}

	vec3 lighting = shadow * result;
	lighting = max(lighting, MIN_SUN_LIGHT);
	lighting = min(lighting, sunLight);

	vec4 texColor = texture(tex, TexCoords);

	if (length(texColor) == 0)
		texColor = vec4(1);

	FragColor = vec4(lighting, 1) * texColor;
}

float calcShadow(LightShadow lightShadow, vec3 lightDir) {
	vec4 lightFragPos = lightShadow.projView * vec4(FragPos, 1);
	vec3 projCoords = lightFragPos.xyz / lightFragPos.w;
	projCoords = (projCoords + 1) * 0.5;

	if (projCoords.z > 1)
		return 1;

	float closestDepth = texture(lightShadow.depthMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	vec2 texelSize = 1 / textureSize(lightShadow.depthMap, 0);
	float bias = max(MIN_SHADOW_BIAS, MAX_SHADOW_BIAS * (1 - max(0, dot(vec3(0, -1, 0), lightDir))));
	float shadow = 0;

	if (SHADOW_INTERPOLATION) {
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				float pcfDepth = texture(lightShadow.depthMap, projCoords.xy + vec2(x, y) * texelSize).r;
	
				if (material.shadow)
					shadow += currentDepth - bias > pcfDepth ? 0 : 1;
			}
		}

		shadow /= 9;
	} else {
		shadow = currentDepth - bias > closestDepth ? 0 : 1;
	}

	return shadow;
}

vec3 calcPointLight (PointLight light) {
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 ambient, diffuse, specular;

	ambient = light.color;

	if (material.diffuseCount > 0) {
		float diff = max(0, dot(Normal, lightDir));
		diffuse = light.color * diff;

		for (int i = 0; i < material.diffuseCount; ++i) {
			diffuse *= vec3(texture(material.diffuse[i], TexCoords));
			ambient *= vec3(texture(material.diffuse[i], TexCoords));
		}
	}

	if (material.specularCount > 0) {
		vec3 reflectDir = reflect(-lightDir, Normal);
		float spec = pow(max(0, dot(cameraPos, reflectDir)), material.shininess);
		specular = light.color * spec;

		for (int i = 0; i < material.specularCount; ++i) {
			specular *= vec3(texture(material.specular[i], TexCoords));
		}
	}

	return ambient + diffuse + specular;
}

float calcAttenuation(PointLight light, float distance) {
	 return 1.0 / (light.constant + light.linear * distance + 
  			       light.quadratic * (distance * distance));
}

vec3 calcSunDiffuse(DirectLight sun) {
	float diff = max(MIN_SUN_DIFFUSE, dot(Normal, -sun.direction));
	vec3 diffuse = diff * sun.color;

	return diffuse;
}

float calcSunLight() {
	float sunLight = clamp(0.15 - sun.direction.y, MIN_SUN_LIGHT, 1);

	return sunLight;
}