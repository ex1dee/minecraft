#include "WindowInput.h"

#include "../../window/Events.h"
#include "../../window/Window.h"

void WindowInput::handle() {
	if (Events::justPressed(GLFW_KEY_F11)) {
		Window::toggleFullscreen();
	}
}