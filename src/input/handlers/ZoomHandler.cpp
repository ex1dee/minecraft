#include "ZoomHandler.h"

#include <glm/glm.hpp>

#include "../../player/Camera.h"
#include "../../math/Mathf.h"
#include "../Input.h"

ZoomHandler::ZoomHandler(float timeSec, float minZoom, float maxZoom)
	: timeSec(timeSec), minZoom(minZoom), maxZoom(maxZoom) {
	duration = 0;
}

void ZoomHandler::handle(Camera& camera, bool zoom, float deltaTime) {
	if (zoom) {
		if (duration <= timeSec) {
			duration = glm::min(timeSec, duration + ZOOM_SPEED);
			
			camera.setZoom(getZoom());
		}
	} else {
		if (duration > 0) {
			duration = glm::max(0.0f, duration - ZOOM_SPEED);

			camera.setZoom(getZoom());
		}
	}
}

float ZoomHandler::getZoom() {
	return Mathf::bezierCurve(minZoom, maxZoom, duration / timeSec, minZoom);
}