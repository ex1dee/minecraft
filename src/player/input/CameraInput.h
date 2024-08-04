#ifndef CAMERAINPUT_H
#define CAMERAINPUT_H

#include "../CameraViewMode.h""
#include "../Player.h"

#define ZOOM_TIME_SEC 0.15f

class CameraInput {
	static float zoomDuration;

	static float getZoom();
	static CameraViewMode getNextViewMode(CameraViewMode currentMode);
public:
	static void handle(Player* player);
};

#endif