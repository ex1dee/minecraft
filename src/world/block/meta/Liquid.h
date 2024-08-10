#ifndef LIQUID_H
#define LIQUID_H

#include "../../../render/fog/Fog.h"
#include "BlockMeta.h"

class Liquid : public BlockMeta {
	float viscosity;
	float speedCoef;
	Fog fog;
public:
	Liquid(float viscosity, const glm::vec4& fog_color, float fog_density)
		: viscosity(viscosity) {
		fog = Fog(fog_color, fog_density);
		speedCoef = 6.0f / viscosity;
	}

	const Fog& getFog() { return fog; }
	float getViscosity() { return viscosity; }
	float getSpeedCoef() { return speedCoef; }
};

#endif