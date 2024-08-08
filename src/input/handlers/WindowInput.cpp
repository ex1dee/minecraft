#include "WindowInput.h"

#include "../../window/Window.h"
#include "../Input.h"

void WindowInput::handle() {
	if (Input::justPressed(GLFW_KEY_F11)) {
		Window::toggleFullscreen();
	}
}