#include "Camera.h"

#include "../world/RayTracing.h"
#include "../window/Window.h"
#include "../config/Config.h"
#include "../input/Input.h"

constexpr float
CAMERA_TPS_COEF = 5.0f,
CAMERA_MAX_PITCH = 89.0f,
CAMERA_INTERSECT_OFFSET = 1.7f;

Camera::Camera() {
	orientation.update(-90.0f, 0.0f);
	aspect = (float) Window::getScreenWidth() / (float) Window::getScreenHeight();
}

void Camera::hookPlayer(std::shared_ptr<Player>& player) {
	this->player = player;
}

void Camera::hookWorld(std::shared_ptr<World>& world) {
	this->world = world;
}

void Camera::setZoom(float zoom) {
	this->zoom = zoom;
}

void Camera::update() {
	fov = Config::settings["camera"]["fov"];

	if (!blocked)
		updateOrientation();

	updateView();
	updateProjection();

	projView = projection * view;
	skyboxView = glm::mat4(glm::mat3(view));
	frustum.update(projView);
}

void Camera::updateOrientation() {
	CursorPos curPos = Input::getCursorPos();
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
	transform.position = player->transform.position + player->getType().eyesOffset;
	viewDir = orientation.front;

	if (viewMode != FIRST_PERSON) {
		updateTPSLook();
	}

	view = glm::lookAt(
		transform.position,
		transform.position + viewDir,
		glm::vec3(0, 1, 0)
	);
}

void Camera::updateTPSLook() {
	float viewSign = (viewMode == THIRD_PERSON_BACK) ? 1.0f : -1.0f;

	Ray ray(transform.position, viewSign * -viewDir);
	std::shared_ptr<Block> block = RayTracing::getNearestBlock(*world, ray, CAMERA_TPS_COEF + CAMERA_INTERSECT_OFFSET);

	if (block != nullptr) {
		IntersectList intersects = block->intersect(ray);
		glm::vec3 pos = intersects.getNearestTo(transform.position);

		viewDir = glm::normalize(transform.position - pos);
		transform.position = pos + viewDir * CAMERA_INTERSECT_OFFSET;
	} else {
		transform.position += viewSign * -orientation.front * CAMERA_TPS_COEF;
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

bool Camera::isAABBInFrustum(const AABB& aabb) const {
	return frustum.isAABBInFrustum(aabb);
}