#ifndef PLAYER_H
#define PLAYER_H

#include "../math/Orientation.h"
#include "../entity/Entity.h"

#define PLAYER_DEFAULT_SPEED 3.0f
#define PLAYER_JUMP_FORCE 5.0f
#define PLAYER_SPRINT_COEF 1.5f
#define PLAYER_SIDE_COEF 0.5f
#define PLAYER_SNEAKING_COEF 0.35f

class Camera;

class Player : public Entity {
	friend class MovementsHandler;

	bool bIsSprinting = false;
	bool bIsSneaking = false;
	bool bIsFlying = true;
	float speed = PLAYER_DEFAULT_SPEED;
	float jumpForce = PLAYER_JUMP_FORCE;

	Camera* camera;
public:
	Player(Camera* camera);

	float getWalkSpeed() { return speed; }
	float getJumpForce() { return jumpForce; }
	bool isFlying() { return bIsFlying; }
	bool isSneaking() { return bIsSneaking; }
	bool isSprinting() { return bIsSprinting; }
	Camera& getCamera() { return *camera; }

	bool isJumping();
	const Orientation& getOrientation();
};

#endif