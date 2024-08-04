#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>

#include "../math/Orientation.h"
#include "../math/Frustum.h"
#include "CameraViewMode.h"
#include "Player.h"

#define CAMERA_OFFSET glm::vec3(0, 1.5f, 0)
#define CAMERA_TPS_COEF 5.0f
#define CAMERA_MAX_PITCH 89.0f
#define CAMERA_NEAR 0.1f
#define CAMERA_FAR 500.0f
#define CAMERA_MAX_ZOOM 30.0f

class Camera {
	glm::mat4 view;
	glm::mat4 projView;
	glm::mat4 skyboxProjView;
	glm::mat4 projection;

	Orientation orientation;
	CameraViewMode viewMode;
	Transform transform;
	Frustum frustum;
	Player* player;
	World* world;

	float aspect;
	float fov;
	float zoom;

	void updatePosition();
	void updateOrientation();
	void updateView();
	void updateProjection();
	glm::vec3 getOffset();
public:
	Camera();

	void update();
	void hookWorld(World* world);
	void hookPlayer(Player* player);
	bool isAABBInFrustum(const AABB& aabb);

	float getZoom() { return zoom; }
	CameraViewMode getViewMode() { return viewMode; }
	const Orientation& getOrientation() { return orientation; }
	const glm::vec3& getPosition() { return transform.position; }
	const glm::mat4& getView() { return view; }
	const glm::mat4& getProjView() { return projView; }
	const glm::mat4& getProjection() { return projection; }
	const glm::mat4& getSkyboxProjView() { return skyboxProjView; }
	void setViewMode(CameraViewMode viewMode) { this->viewMode = viewMode; }
	void setZoom(float zoom) { this->zoom = zoom; }
};

#endif