#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "../player/Player.h"
#include "../world/World.h"
#include "BaseState.h"

class PlayState : public BaseState {
	World* world;
	Player* player;
	Camera* camera;
public:
	PlayState(Renderer* renderer, Player* player, Camera* camera);
	~PlayState();

	void handleInput() override;
	void update() override;
	void render() override;
};

#endif