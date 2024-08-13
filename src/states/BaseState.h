#ifndef BASESTATE_H
#define BASESTATE_H

#include "../render/Renderer.h"

class BaseState {
public:
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif