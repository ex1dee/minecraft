#ifndef PLAYER_H
#define PLAYER_H

#include "../math/geometry/Orientation.h"
#include "../entity/Entity.h"

constexpr float
PLAYER_DEFAULT_SPEED = 5.75f,
PLAYER_JUMP_FORCE = 12.5f,
PLAYER_INLIQUID_JUMP_COEF = 0.5f,
PLAYER_INLIQUID_SWIM_COEF = 0.7f,
PLAYER_SPRINT_COEF = 1.5f,
PLAYER_SIDE_COEF = 0.5f,
PLAYER_FLYING_COEF = 10.0f,
PLAYER_SNEAKING_COEF = 0.35f;

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
	Player(Camera& camera);

	float getWalkSpeed() const { return speed; }
	float getJumpForce() const { return jumpForce; }
	bool isFlying() const { return flying; }
	bool isSneaking() const { return sneaking; }
	bool isSprinting() const { return sprinting; }
	Camera& getCamera() const { return *camera; }

	void setFlying(bool flying);
};

#endif