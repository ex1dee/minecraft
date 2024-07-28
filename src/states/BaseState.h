#ifndef BASESTATE_H
#define BASESTATE_H

#include "../render/Renderer.h"

class BaseState {
protected:
	Renderer* renderer;
public:
	BaseState(Renderer* renderer)
		: renderer(renderer) {}

	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif