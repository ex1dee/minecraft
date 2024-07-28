#include "PlayState.h"

PlayState::PlayState(Renderer* renderer, Player& player, Camera& camera)
	: BaseState(renderer), player(player), camera(camera) {
	
	camera.hookPlayer(player);
	world = new World(new SuperFlatGenerator, player, camera);
}

PlayState::~PlayState() {
	delete world;
}

void PlayState::handleInput() {

}

void PlayState::update() {
	world->update(*renderer, player, camera);
}

void PlayState::render() {
	world->render(*renderer, camera);
}