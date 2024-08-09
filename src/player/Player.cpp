#include "Player.h"

#include "../world/World.h"
#include "Camera.h"

Player::Player(Camera* camera)
	: camera(camera), Entity(PLAYER) {
	
}