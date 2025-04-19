#ifndef CAMERAINPUT_H
#define CAMERAINPUT_H

#include "../../player/CameraViewMode.h"
#include "../../player/Player.h"
#include "ZoomHandler.h"

class CameraInput {
	static ZoomHandler zoom;

	static CameraViewMode getNextViewMode(CameraViewMode currentMode);
public:
	static void handle(Player& player, float deltaTime);
};

#endif