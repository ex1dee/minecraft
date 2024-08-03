#include "Camera.h"

#include "../window/Window.h"
#include "../window/Events.h"
#include "../config/Config.h"
#include "Player.h"

Camera::Camera() {
	pitch = 0;
	yaw = -90;
}

void Camera::hookPlayer(Player* player) {
	this->player = player;
}

void Camera::update() {
	fov = Config::settings["camera"]["fov"];
	aspect = (float)Window::getWidth() / (float)Window::getHeight();

	updatePosition();
	updateOrientation();
	updateView();
	updateProjection();

	projView = projection * view;
	skyboxProjView = projection * glm::mat4(glm::mat3(view));
	frustum.update(projView);
}

void Camera::updatePosition() {
	if (player == nullptr)
		return;

	transform.position = player->transform.position + CAMERA_OFFSET;
}

void Camera::updateOrientation() {
	CursorPos curPos = Events::getCursorPos();
	curPos.delta *= Config::settings["camera"]["sensitivity"];

	yaw += curPos.delta.x;
	pitch -= curPos.delta.y;

	if (pitch > CAMERA_MAX_PITCH)
		pitch = CAMERA_MAX_PITCH;
	if (pitch < -CAMERA_MAX_PITCH)
		pitch = -CAMERA_MAX_PITCH;

	orientation.update(yaw, pitch);
}

void Camera::updateView() {
	view = glm::lookAt(
		transform.position,
		transform.position + orientation.front,
		glm::vec3(0, 1, 0)
	);
}

void Camera::updateProjection() {
	projection = glm::perspective(
		glm::radians(fov),
		aspect,
		CAMERA_NEAR,
		CAMERA_FAR
	);
}

bool Camera::isAABBInFrustum(const AABB& aabb) {
	return frustum.isAABBInFrustum(aabb);
}