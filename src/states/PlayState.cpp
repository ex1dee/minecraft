#include "PlayState.h"

#include "../player/input/MovementsInput.h"
#include "../player/input/CameraInput.h"
#include "../player/input/WindowInput.h"
#include "../physics/PhysicsEngine.h"
#include "../gui/GUI.h"
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
	WindowInput::handle();
}

void PlayState::update() {
	Time::update();

	if (Time::isTickElapsed()) {
		world->update(*renderer, *player, *camera);

		PhysicsEngine::updatePerLongTick(*player);
	} else {
		if (Time::isPhysicsTickElapsed())
			PhysicsEngine::updatePerTick(*player);
	}

	GUI::update();
}

void PlayState::render() {
	world->render(*renderer, *player);

	renderer->finishRender(*player, camera, *world);
}