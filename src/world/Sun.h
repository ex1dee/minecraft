#ifndef SUN_H
#define SUN_H

#include "../render/light/DirectLight.h"
#include "../player/Player.h"

class World;

class Sun {
	glm::vec3 focus;
	DirectLight* light;
	Player* player;
	World* world;
	
	glm::vec3& getFocus();
	float calcAngle(float time);
public:
	Sun(Shader& FBOShader, World& world, Player& player);
	~Sun();

	DirectLight& getLight() const { return *light; }

	void setTime(float time);
};

#endif