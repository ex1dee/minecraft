#ifndef PLAYER_H
#define PLAYER_H

#include "../entity/Entity.h"

class Player : public Entity {
	bool bIsFlying = true;
public:
	Player();

	bool isFlying() { return bIsFlying; }
};

#endif