#include "CameraInput.h"

#include "../../window/Events.h"
#include "../../math/Math.h"
#include "../../Time.h"
#include "../Camera.h"

float CameraInput::zoomDuration = 0;

void CameraInput::handle(Player* player) {
	Camera* camera = player->getCamera();
	
	if (Events::justPressed(GLFW_KEY_F5)) {
		camera->setViewMode(getNextViewMode(camera->getViewMode()));
	}

	if (Events::pressed(GLFW_KEY_C)) {
		if (zoomDuration <= ZOOM_TIME_SEC) {
			zoomDuration = glm::min(ZOOM_TIME_SEC, zoomDuration + Time::getDeltaTime());

			camera->setZoom(getZoom());
		}
	} else {
		if (zoomDuration > 0) {
			zoomDuration = glm::max(0.0f, zoomDuration - Time::getDeltaTime());

			camera->setZoom(getZoom());
		}
	}
}

float CameraInput::getZoom() {
	return bezcurve(0, CAMERA_MAX_ZOOM, zoomDuration / ZOOM_TIME_SEC);
}

CameraViewMode CameraInput::getNextViewMode(CameraViewMode currentMode) {
	if (currentMode == FIRST_PERSON) {
		return THIRD_PERSON_BACK;
	} else if (currentMode == THIRD_PERSON_BACK) {
		return THIRD_PERSON_FRONT;
	} else {
		return FIRST_PERSON;
	}
}