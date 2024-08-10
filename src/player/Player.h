#ifndef PLAYER_H
#define PLAYER_H

#include "../math/geometry/Orientation.h"
#include "../entity/Entity.h"

#define PLAYER_DEFAULT_SPEED 5.75f
#define PLAYER_JUMP_FORCE 12.5f
#define PLAYER_INLIQUID_JUMP_COEF 0.5f
#define PLAYER_INLIQUID_SWIM_COEF 0.7f
#define PLAYER_SPRINT_COEF 1.5f
#define PLAYER_SIDE_COEF 0.5f
#define PLAYER_FLYING_COEF 10.0f
#define PLAYER_SNEAKING_COEF 0.35f

class Camera;

class Player : public Entity {
	friend class MovementsInput;

	bool sprinting = false;
	bool sneaking = false;
	bool flying = false;
	float speed = PLAYER_DEFAULT_SPEED;
	float jumpForce = PLAYER_JUMP_FORCE;

	Camera* camera;
public:
	Player(Camera* camera);

	float getWalkSpeed() { return speed; }
	float getJumpForce() { return jumpForce; }
	bool isFlying() { return flying; }
	bool isSneaking() { return sneaking; }
	bool isSprinting() { return sprinting; }
	Camera* const getCamera() { return camera; }

	bool isEyesInWater();
	void setFlying(bool flying);
};

#endif