#ifndef CAMERA_H
#define CAMERA_H

#include "../GL/GLHelper.h"

#include "../math/geometry/Orientation.h"
#include "../math/shapes/Frustum.h"
#include "CameraViewMode.h"
#include "Player.h"

constexpr float
CAMERA_MAX_ZOOM = 30.0f,
CAMERA_NEAR = 0.1f,
CAMERA_FAR = 500.0f;

class Camera {
	glm::mat4 view;
	glm::mat4 projView;
	glm::mat4 skyboxView;
	glm::mat4 projection;
	glm::vec3 viewDir;

	std::shared_ptr<Player> player;
	std::shared_ptr<World> world;
	Transform transform;
	Frustum frustum;

	CameraViewMode viewMode = CameraViewMode::FIRST_PERSON;
	bool blocked = false;
	float zoom = 0;
	float aspect;
	float fov;

	void updateTPSLook();
	void updateOrientation();
	void updateView();
	void updateProjection();
public:
	Camera();

	float getZoom() const { return zoom; }
	CameraViewMode getViewMode() const { return viewMode; }
	const glm::vec3& getPosition() const { return transform.position; }
	const glm::mat4& getView() const { return view; }
	const glm::mat4& getProjView() const { return projView; }
	const glm::mat4& getProjection() const { return projection; }
	const glm::mat4& getSkyboxView() const { return skyboxView; }
	void setBlocked(bool blocked) { this->blocked = blocked; }
	void setViewMode(CameraViewMode viewMode) { this->viewMode = viewMode; }

	void update();
	void setZoom(float zoom);
	void hookWorld(std::shared_ptr<World>& world);
	void hookPlayer(std::shared_ptr<Player>& player);
	bool isAABBInFrustum(const AABB& aabb) const;
};

#endif