#version 330 core

#define PI 3.1415926538
#define dPI 2 * PI
#define hPI 0.5 * PI

#define DAY_COLOR vec3(0.3, 0.52, 0.68)
#define NIGHT_COLOR vec3(0, 0, 0)
#define HORIZON_COLOR vec3(0.949, 0.49, 0)
#define SUN_COLOR vec3(1, 1, 0.8)
#define MOON_COLOR vec3(0.6, 0.6, 0.6)

#define FOG_ZSTART 0.0
#define FOG_ZEND 3.0

struct Fog {
	bool enabled;
	int type;

	float density;
	float zStart;
	float zEnd;
	vec4 color;
};

out vec4 FragColor;
in vec3 FragPos;

uniform samplerCube background;
uniform vec3 lightDir;
uniform Fog fog;

mat4 rotationMatrix(vec3 axis, float angle);
float angV3(vec3 v1, vec3 v2);
float calcFogFactor();

void main() {
	vec3 rp = normalize(-FragPos);
	vec2 uv = vec2(atan(rp.z, rp.x)/dPI, (asin(rp.y) + hPI)/PI);

	float ang_sun = angV3(rp, lightDir);
	float dot_sun = max(0, cos(ang_sun));
	float mulDot_sun = pow(dot_sun, 10);
	float sun_mask = smoothstep(0, 1.5, mulDot_sun) * 2;

	float ang_moon = angV3(rp, -lightDir);
	float dot_moon = max(0, cos(ang_moon));
	float mulDot_moon = pow(dot_moon, 20);
	float moon_mask = smoothstep(0.8, 1, mulDot_moon) * 10;

	float light_mask = smoothstep(-1, 1, lightDir.y);
	float horizon_mask = pow(smoothstep(0.40, 0.52, uv.y - 0.02), 2);
	float horizon_activation = pow(smoothstep(0.25, 0, lightDir.y * 0.5), 1) * pow(smoothstep(-0.2, 0.15, lightDir.y * 0.5), 1);
	float background_mask = max(0, lightDir.y - 0.25);

	vec3 clr = mix(DAY_COLOR, NIGHT_COLOR, light_mask);
	if (sun_mask < 1)
		clr = mix(clr, HORIZON_COLOR, horizon_mask * horizon_activation * dot_sun * 5);
	clr = mix(clr, SUN_COLOR, sun_mask);
	clr = mix(clr, MOON_COLOR, moon_mask);

	float sgn = 1;
	if (lightDir.x > 0)
		sgn = -1;

	float ang_light = sgn * angV3(vec3(0, 1, 0), lightDir) * 0.5;
	vec3 rotBackPos = vec3(rotationMatrix(vec3(0, 0, 1), ang_light) * vec4(FragPos, 1));

	if (ang_moon > 0.15)
		clr = mix(clr, vec3(texture(background, rotBackPos)), background_mask);

	FragColor = vec4(clr, 1);
	
	if (fog.enabled)
		FragColor = mix(FragColor, fog.color, calcFogFactor());
}

float calcFogFactor() {
	return fog.type != 0 ? 1.0 : 0.0;
}

mat4 rotationMatrix(vec3 axis, float angle) {
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

float angV3(vec3 v1, vec3 v2) { 
	return acos(dot(normalize(v1), normalize(v2)));
}