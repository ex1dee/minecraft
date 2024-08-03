#ifndef SUN_H
#define SUN_H

#include "light/DirectLight.h"
#include "../player/Player.h"

#define CHANGE_FOCUS_DIST CHUNK_W * 4.0f

class World;

class Sun {
	static glm::vec3 prevFocus;
public:
	static DirectLight* light;

	static void initialize(Shader* FBOShader);
	static void finalize();

	static void setTime(float time, Player& player, World* world);
};

#endif