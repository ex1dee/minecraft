#include "PlayState.h"

#include "../input/handlers/MovementsInput.h"
#include "../input/handlers/CameraInput.h"
#include "../input/handlers/WindowInput.h"
#include "../physics/PhysicsEngine.h"
#include "../gui/GUI.h"

PlayState::PlayState(Renderer* renderer, Player* player, Camera* camera)
	: BaseState(renderer), player(player), camera(camera) {

	world = new World(*player);

	PhysicsEngine::initialize(world);
	camera->hookPlayer(player);
	camera->hookWorld(world);

	worldTickTimer.start(SEC_PER_WORLD_TICK, &isRunning);
	physicsTickTimer.start(SEC_PER_PHYSICS_TICK, &isRunning);
}

PlayState::~PlayState() {
	PhysicsEngine::finalize();
	isRunning = false;

	delete world;
}

void PlayState::handleInput() {
	MovementsInput::handle(player, physicsTickTimer.getSecPerTick());
	CameraInput::handle(player, physicsTickTimer.getSecPerTick());
	WindowInput::handle();
}

void PlayState::update() {
	if (worldTickTimer.isTickElapsed()) {
		world->update(*renderer, *player);
	}

	if (physicsTickTimer.isTickElapsed()) {
		PhysicsEngine::update(*player, physicsTickTimer.getSecPerTick());
	}

	GUI::update();
}

void PlayState::render() {
	world->render(*renderer, *player);

	renderer->finishRender(*player, camera, *world);
}