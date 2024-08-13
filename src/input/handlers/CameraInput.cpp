#include "CameraInput.h"

#include <GLFW/glfw3.h>

#include "../../player/Camera.h"
#include "../Input.h"

constexpr float ZOOM_TIME_SEC = 0.15f;

ZoomHandler CameraInput::zoom = ZoomHandler(ZOOM_TIME_SEC, 0, CAMERA_MAX_ZOOM);

void CameraInput::handle(Player& player, float deltaTime) {
	Camera& camera = player.getCamera();
	
	if (Input::justPressed(GLFW_KEY_F5)) {
		camera.setViewMode(getNextViewMode(camera.getViewMode()));
	}

	if (camera.getZoom() >= 0)
		zoom.handle(camera,
			Input::pressed(GLFW_KEY_C) && !(Input::pressed(GLFW_KEY_W) && Input::pressed(GLFW_KEY_LEFT_CONTROL)), 
			deltaTime
		);
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