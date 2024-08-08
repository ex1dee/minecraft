#include "ZoomHandler.h"

#include <glm/glm.hpp>

#include "../../player/Camera.h"
#include "../../utils/Time.h"
#include "../../math/Mathf.h"
#include "../Input.h"

ZoomHandler::ZoomHandler(float timeSec, float minZoom, float maxZoom)
	: timeSec(timeSec), minZoom(minZoom), maxZoom(maxZoom) {
	duration = 0;
}

void ZoomHandler::handle(Camera* camera, bool zoom) {
	if (zoom) {
		if (duration <= timeSec) {
			duration = glm::min(timeSec, duration + Time::getDeltaTime());
			
			camera->setZoom(getZoom());
		}
	} else {
		if (duration > 0) {
			duration = glm::max(0.0f, duration - Time::getDeltaTime());

			camera->setZoom(getZoom());
		}
	}
}

float ZoomHandler::getZoom() {
	return Mathf::bezierCurve(minZoom, maxZoom, duration / timeSec, minZoom);
}