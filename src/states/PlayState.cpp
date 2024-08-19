#include "PlayState.h"

#include "../input/handlers/MovementsInput.h"
#include "../input/handlers/CameraInput.h"
#include "../input/handlers/WindowInput.h"
#include "../input/handlers/GUIInput.h"
#include "../physics/PhysicsEngine.h"
#include "../gui/GUI.h"

constexpr float
SEC_PER_PHYSICS_TICK = 1.0f / 120.0f,
SEC_PER_WORLD_TICK = 0.005f;

PlayState::PlayState(Player& player)
	: player(&player) {

	renderer = new Renderer(player);
	world = new World(player, *renderer);
	camera = &player.getCamera();

	PhysicsEngine::initialize(*world);
	camera->hookPlayer(player);
	camera->hookWorld(*world);

	worldTickTimer.start(SEC_PER_WORLD_TICK, &isRunning);
	physicsTickTimer.start(SEC_PER_PHYSICS_TICK, &isRunning);
}

PlayState::~PlayState() {
	PhysicsEngine::finalize();
	isRunning = false;

	freePointer(&world);
	freePointer(&renderer);
}

void PlayState::handleInput() {
	GUIInput::handle(*player);
	MovementsInput::handle(*player, physicsTickTimer.getSecPerTick());
	CameraInput::handle(*player, physicsTickTimer.getSecPerTick());
	WindowInput::handle();
}

void PlayState::update() {
	if (worldTickTimer.isTickElapsed()) {
		world->update(worldTickTimer.getSecPerTick());
	}

	if (physicsTickTimer.isTickElapsed()) {
		PhysicsEngine::update(physicsTickTimer.getSecPerTick());
	}

	GUI::update(*player);
}

void PlayState::render() {
	world->render();

	renderer->finishRender(*world);
}