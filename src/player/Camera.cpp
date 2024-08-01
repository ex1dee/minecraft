#include "Camera.h"

#include "../window/Window.h"
#include "../window/Events.h"
#include "../config/Config.h"

Camera::Camera() {
	pitch = 0;
	yaw = -90;
}

Camera::~Camera() {
	
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

	transform.position = player->transform.position + glm::vec3(0, 1.5, 0);
}

void Camera::updateOrientation() {
	CursorPos curPos = Events::getCursorPos();
	curPos.delta *= Config::settings["camera"]["sensitivity"];
	curPos.delta.y *= -1;

	yaw += curPos.delta.x;
	pitch += curPos.delta.y;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

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

bool Camera::isAABBInFrustum(AABB& aabb) {
	return frustum.isAABBInFrustum(aabb);
}