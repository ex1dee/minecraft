#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>
#include <thread>

#include "player/Player.h"
#include "world/World.h"
#include "utils/Timer.h"

class PlayState {
	std::atomic<bool> isRunning;
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<World> world;

	Timer worldTickTimer;
	Timer physicsTickTimer;
public:
	PlayState(std::shared_ptr<Player>& player);
	~PlayState();

	void handleInput();
	void update();
	void render();
};

#endif