#ifndef SUN_H
#define SUN_H

#include "../render/light/DirectLight.h"
#include "../player/Player.h"

#define CHANGE_FOCUS_DIST CHUNK_W * 4.0f

class World;

class Sun {
	glm::vec3 prevFocus;
	DirectLight* light;
	World* world;
	
	glm::vec3& getFocus(Player& player);
	float calcAngle(float time);
public:
	Sun(Shader* FBOShader, World* world);
	~Sun();

	DirectLight& getLight() const { return *light; }

	void setTime(float time, Player& player);
};

#endif