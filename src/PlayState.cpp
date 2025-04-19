#include "PlayState.h"

#include "input/handlers/BlockInteractsInput.h"
#include "input/handlers/MovementsInput.h"
#include "input/handlers/InventoryInput.h"
#include "input/handlers/CameraInput.h"
#include "input/handlers/WindowInput.h"
#include "input/handlers/HitHandler.h"

#include "physics/PhysicsEngine.h"
#include "gui/GUI.h"

constexpr float
SEC_PER_PHYSICS_TICK = 1.0f / 120.0f,
SEC_PER_WORLD_TICK = 1.0f / 20.0f;

PlayState::PlayState(std::shared_ptr<Player>& player)
	: player(player) {

	renderer = std::make_shared<Renderer>(player);
	world = std::make_shared<World>(player, renderer);
	camera = player->camera;

	PhysicsEngine::initialize(*world);
	camera->hookPlayer(player);
	camera->hookWorld(world);

	worldTickTimer.start(SEC_PER_WORLD_TICK, &isRunning);
	physicsTickTimer.start(SEC_PER_PHYSICS_TICK, &isRunning);
}

PlayState::~PlayState() {
	isRunning = false;
}

void PlayState::handleInput() {
	InventoryInput::handle(*player);
	BlockInteractsInput::handle(*player, *world, physicsTickTimer.getSecPerTick());
	MovementsInput::handle(*player, physicsTickTimer.getSecPerTick());
	CameraInput::handle(*player, physicsTickTimer.getSecPerTick());
	HitHandler::handle(*player);
	WindowInput::handle();
}

void PlayState::update() {
	if (worldTickTimer.isTickElapsed()) {
		world->update(worldTickTimer.getSecPerTick());
	}

	world->playAnimations(physicsTickTimer.getSecPerTick());

	if (physicsTickTimer.isTickElapsed()) {
		PhysicsEngine::update(physicsTickTimer.getSecPerTick());
	}

	GUI::update(*player);
}

void PlayState::render() {
	world->render();

	renderer->finishRender(*world);
}