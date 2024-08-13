#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>
#include <thread>

#include "../player/Player.h"
#include "../world/World.h"
#include "../utils/Timer.h"
#include "BaseState.h"

class PlayState : public BaseState {
	std::atomic<bool> isRunning;
	Renderer* renderer;
	Player* player;
	Camera* camera;
	World* world;

	Timer worldTickTimer;
	Timer physicsTickTimer;
public:
	PlayState(Player& player);
	~PlayState();

	void handleInput() override;
	void update() override;
	void render() override;
};

#endif