#include "CameraInput.h"

#include <GLFW/glfw3.h>

#include "../../window/Events.h"
#include "../../player/Camera.h"

ZoomHandler CameraInput::zoom = ZoomHandler(ZOOM_TIME_SEC, 0, CAMERA_MAX_ZOOM);

void CameraInput::handle(Player* player) {
	Camera* camera = player->getCamera();
	
	if (Events::justPressed(GLFW_KEY_F5)) {
		camera->setViewMode(getNextViewMode(camera->getViewMode()));
	}

	if (camera->getZoom() >= 0)
		zoom.handle(camera, Events::pressed(GLFW_KEY_C) && !(Events::pressed(GLFW_KEY_W) && Events::pressed(GLFW_KEY_LEFT_CONTROL)));
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