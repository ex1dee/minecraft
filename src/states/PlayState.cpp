#include "PlayState.h"

#include "../physics/PhysicsEngine.h"
#include "../Time.h"

PlayState::PlayState(Renderer* renderer, Player* player, Camera* camera)
	: BaseState(renderer), player(player), camera(camera) {
	
	camera->hookPlayer(player);
	world = new World(new SuperFlatGenerator, *player, *camera);

	PhysicsEngine::initialize(world);
}

PlayState::~PlayState() {
	PhysicsEngine::finalize();

	delete world;
}

void PlayState::handleInput() {
	
}

void PlayState::update() {
	world->updateChunks(*camera);

	if (Time::needUpdate()) {
		world->update(*renderer, *player, *camera);

		PhysicsEngine::updatePerTick();
	} else {
		PhysicsEngine::updatePerFrame();
	}
}

void PlayState::render() {
	world->render(*renderer, *camera);
}