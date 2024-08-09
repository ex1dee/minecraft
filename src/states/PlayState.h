#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>
#include <thread>

#include "../player/Player.h"
#include "../world/World.h"
#include "../utils/Timer.h"
#include "BaseState.h"

#define SEC_PER_PHYSICS_TICK 1.0 / 120.0
#define SEC_PER_WORLD_TICK 0.005

class PlayState : public BaseState {
	std::atomic<bool> isRunning;
	World* world;
	Player* player;
	Camera* camera;

	Timer worldTickTimer;
	Timer physicsTickTimer;
public:
	PlayState(Renderer* renderer, Player* player, Camera* camera);
	~PlayState();

	void handleInput() override;
	void update() override;
	void render() override;
};

#endif