#include "PlayState.h"

#include "../player/input/MovementsHandler.h"
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
	MovementsHandler::handle(player);
}

void PlayState::update() {
	world->updateChunks(*camera);

	if (Time::needUpdate()) {
		world->update(*renderer, *player, *camera);

		PhysicsEngine::updatePerTick(*player);
	} else {
		PhysicsEngine::updatePerFrame(*player);
	}
}

void PlayState::render() {
	world->render(*renderer, *camera);
}