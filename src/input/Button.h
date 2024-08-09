#ifndef BUTTON_H
#define BUTTON_H

#include <cstdint>

struct Button {
	bool pressed = false;
	uint64_t pressFrame = 0;
};

#endif