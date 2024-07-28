#include "Camera.h"

#include "../window/Window.h"
#include "../window/Events.h"
#include "../config/Config.h"

Camera::Camera() {
	transform = new Transform;

	pitch = 0;
	yaw = -90;
}

Camera::~Camera() {
	delete transform;
}

void Camera::hookPlayer(Player& player) {
	this->player = &player;
}

glm::mat4& Camera::getView() {
	return view;
}

glm::mat4& Camera::getProjection() {
	return projection;
}

void Camera::update() {
	fov = Config::settings["camera"]["fov"];
	aspect = (float)Window::getWidth() / (float)Window::getHeight();

	updatePosition();
	updateOrientation();
	updateView();
	updateProjection();

	projView = projection * view;
	frustum.update(projView);
}

void Camera::updatePosition() {
	if (player == nullptr)
		return;

	glm::vec3 playerPos = player->transform->position;
	
	transform->position = glm::vec3(playerPos.x, playerPos.y + 1.5, playerPos.z);
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

	transform->update(yaw, pitch);
}

void Camera::updateView() {
	view = glm::lookAt(
		transform->position,
		transform->position + transform->front,
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