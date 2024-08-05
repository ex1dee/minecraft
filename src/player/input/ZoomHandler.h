#ifndef ZOOMHANDLER_H
#define ZOOMHANDLER_H

class Camera;

class ZoomHandler {
	float duration;
	float timeSec;
	float minZoom;
	float maxZoom;

	float getZoom();
public:
	ZoomHandler(float timeSec, float minZoom, float maxZoom);

	void handle(Camera* camera, bool zoom);
};

#endif