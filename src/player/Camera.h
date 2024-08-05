#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>

#include "../math/geometry/Orientation.h"
#include "../math/shapes/Frustum.h"
#include "CameraViewMode.h"
#include "Player.h"

#define CAMERA_TPS_COEF 5.0f
#define CAMERA_MAX_PITCH 89.0f
#define CAMERA_NEAR 0.1f
#define CAMERA_FAR 500.0f
#define CAMERA_MAX_ZOOM 30.0f
#define CAMERA_INTERSECT_OFFSET 1.4f

class Camera {
	glm::mat4 view;
	glm::mat4 projView;
	glm::mat4 skyboxProjView;
	glm::mat4 projection;

	glm::vec3 viewPos;
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
	void setZoom(float zoom);
};

#endif