#ifndef SUN_H
#define SUN_H

#include "light/DirectLight.h"
#include "../player/Player.h"

class Sun {
public:
	static DirectLight* light;

	static void initialize(Shader* FBOShader);
	static void finalize();

	static void setTime(float time, const Player& player);
};

#endif