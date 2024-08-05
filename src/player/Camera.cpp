#include "Camera.h"

#include "../world/RayTracing.h"
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

void Camera::setZoom(float zoom) {
	this->zoom = zoom;
}

void Camera::update() {
	fov = Config::settings["camera"]["fov"];
	aspect = (float)Window::getWidth() / (float)Window::getHeight();

	updateOrientation();
	updateView();
	updateProjection();

	projView = projection * view;
	skyboxProjView = projection * glm::mat4(glm::mat3(view));
	frustum.update(projView);
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
	viewPos = player->transform.position + player->getType()->eyesOffset;
	viewDir = orientation.front;

	if (viewMode != FIRST_PERSON) {
		updateTPSLook();
	}

	view = glm::lookAt(
		viewPos,
		viewPos + viewDir,
		glm::vec3(0, 1, 0)
	);
}

void Camera::updateTPSLook() {
	float viewSign = (viewMode == THIRD_PERSON_BACK) ? 1.0f : -1.0f;

	Ray ray(viewPos, viewSign * -viewDir);
	Block* block = RayTracing::getNearestBlock(world, ray, CAMERA_TPS_COEF + CAMERA_INTERSECT_OFFSET);

	if (block != nullptr) {
		IntersectList intersects = block->intersect(ray);
		glm::vec3 pos = intersects.getNearestTo(viewPos);

		viewDir = glm::normalize(viewPos - pos);
		viewPos = pos + viewDir * CAMERA_INTERSECT_OFFSET;
	} else {
		viewPos += viewSign * -orientation.front * CAMERA_TPS_COEF;
		viewDir *= viewSign;
	}
}

void Camera::updateProjection() {
	projection = glm::perspective(
		glm::radians(fov - glm::min(zoom, CAMERA_MAX_ZOOM)),
		aspect,
		CAMERA_NEAR,
		CAMERA_FAR
	);
}

bool Camera::isAABBInFrustum(const AABB& aabb) {
	return frustum.isAABBInFrustum(aabb);
}