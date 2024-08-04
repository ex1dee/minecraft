#include "PlayState.h"

#include "../player/input/MovementsInput.h"
#include "../player/input/CameraInput.h"
#include "../physics/PhysicsEngine.h"
#include "../Time.h"

PlayState::PlayState(Renderer* renderer, Player* player, Camera* camera)
	: BaseState(renderer), player(player), camera(camera) {

	world = new World(new SuperFlatGenerator, *player, *camera);

	PhysicsEngine::initialize(world);
	camera->hookPlayer(player);
	camera->hookWorld(world);
}

PlayState::~PlayState() {
	PhysicsEngine::finalize();

	delete world;
}

void PlayState::handleInput() {
	MovementsInput::handle(player);
	CameraInput::handle(player);
}

void PlayState::update() {
	if (Time::needUpdate()) {
		world->update(*renderer, *player, *camera);

		PhysicsEngine::updatePerTick(*player);
	} else {
		PhysicsEngine::updatePerFrame(*player);
	}
}

void PlayState::render() {
	world->render(*renderer, *player);

	renderer->finishRender(*player, camera, *world);
}