#ifndef LIQUID_H
#define LIQUID_H

#include "BlockMeta.h"

class Liquid : public BlockMeta {
	float viscosity;
	float speedCoef;
public:
	Liquid(float viscosity)
		: viscosity(viscosity) {
		speedCoef = 6.0f / viscosity;
	}

	float getViscosity() { return viscosity; }
	float getSpeedCoef() { return speedCoef; }

	Liquid* clone() const override {
		return new Liquid(viscosity);
	}
};

#endif