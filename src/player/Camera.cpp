#include "Camera.h"

#include "../window/Window.h"
#include "../window/Events.h"
#include "../config/Config.h"

Camera::Camera() {
	orientation.update(-90.0f, 0.0f);

	zoom = 0;
}

void Camera::hookPlayer(Player* player) {
	this->player = player;
}

void Camera::hookWorld(World* world) {
	this->world = world;
}

void Camera::update() {
	fov = Config::settings["camera"]["fov"];
	aspect = (float)Window::getWidth() / (float)Window::getHeight();

	updateOrientation();
	updatePosition();
	updateView();
	updateProjection();

	projView = projection * view;
	skyboxProjView = projection * glm::mat4(glm::mat3(view));
	frustum.update(projView);
}

void Camera::updatePosition() {
	transform.position = player->transform.position + getOffset();
}

glm::vec3 Camera::getOffset() {
	glm::vec3 offset = CAMERA_OFFSET;

	if (viewMode == THIRD_PERSON_BACK)
		offset -= orientation.front * CAMERA_TPS_COEF;
	else if (viewMode == THIRD_PERSON_FRONT)
		offset += orientation.front * CAMERA_TPS_COEF;

	return offset;
}

void Camera::updateOrientation() {
	CursorPos curPos = Events::getCursorPos();
	curPos.delta *= Config::settings["camera"]["sensitivity"];

	float yaw	= orientation.getYaw() + curPos.delta.x;
	float pitch = orientation.getPitch() - curPos.delta.y;

	if (pitch > CAMERA_MAX_PITCH)
		pitch = CAMERA_MAX_PITCH;
	if (pitch < -CAMERA_MAX_PITCH)
		pitch = -CAMERA_MAX_PITCH;

	orientation.update(yaw, pitch);
	player->orientation = orientation;
}

void Camera::updateView() {
	float frontSign = (viewMode == THIRD_PERSON_FRONT) ? -1.0f : 1.0f;
	
	view = glm::lookAt(
		transform.position,
		transform.position + frontSign * orientation.front,
		glm::vec3(0, 1, 0)
	);
}

void Camera::updateProjection() {
	projection = glm::perspective(
		glm::radians(fov - glm::clamp(zoom, 0.0f, CAMERA_MAX_ZOOM)),
		aspect,
		CAMERA_NEAR,
		CAMERA_FAR
	);
}

bool Camera::isAABBInFrustum(const AABB& aabb) {
	return frustum.isAABBInFrustum(aabb);
}