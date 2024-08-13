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

	Orientation orientation;
	CameraViewMode viewMode;
	Transform transform;
	Frustum frustum;
	Player* player;
	World* world;

	float aspect;
	float fov;
	float zoom;

	void updateTPSLook();
	void updateOrientation();
	void updateView();
	void updateProjection();
public:
	Camera();

	float getZoom() const { return zoom; }
	CameraViewMode getViewMode() const { return viewMode; }
	const Orientation& getOrientation() const { return orientation; }
	const glm::vec3& getPosition() const { return transform.position; }
	const glm::mat4& getView() const { return view; }
	const glm::mat4& getProjView() const { return projView; }
	const glm::mat4& getProjection() const { return projection; }
	const glm::mat4& getSkyboxView() const { return skyboxView; }
	void setViewMode(CameraViewMode viewMode) { this->viewMode = viewMode; }

	void update();
	void setZoom(float zoom);
	void hookWorld(World& world);
	void hookPlayer(Player& player);
	bool isAABBInFrustum(const AABB& aabb) const;
};

#endif