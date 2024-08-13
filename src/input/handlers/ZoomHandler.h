#ifndef ZOOMHANDLER_H
#define ZOOMHANDLER_H

#define ZOOM_SPEED 0.006f

class Camera;

class ZoomHandler {
	float duration;
	float timeSec;
	float minZoom;
	float maxZoom;

	float getZoom();
public:
	ZoomHandler(float timeSec, float minZoom, float maxZoom);

	void handle(Camera& camera, bool zoom, float deltaTime);
};

#endif