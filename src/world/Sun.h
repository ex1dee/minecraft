#ifndef SUN_H
#define SUN_H

#include "../render/light/DirectLight.h"
#include "../player/Player.h"

class World;

class Sun {
	std::unique_ptr<DirectLight> light;
	std::shared_ptr<Player> player;
	glm::vec3 focus;
	World* world;
	
	glm::vec3& getFocus();
	float calcAngle(float time);
public:
	Sun(Shader& FBOShader, World& world, std::shared_ptr<Player>& player);

	DirectLight& getLight() const { return *light; }

	void setTime(float time);
};

#endif