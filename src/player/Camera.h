#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../math/Orientation.h"
#include "../math/Frustum.h"
#include "Player.h"

#define CAMERA_OFFSET glm::vec3(0, 1.5f, 0)
#define CAMERA_MAX_PITCH 89.0f
#define CAMERA_NEAR 0.1f
#define CAMERA_FAR 100.0f

class Camera {
	Orientation orientation;
	glm::mat4 view;
	glm::mat4 projView;
	glm::mat4 skyboxProjView;
	glm::mat4 projection;
	Frustum frustum;
	float aspect;
	float fov;
	float yaw;
	float pitch;
	Player* player;
	Transform transform;

	void updateFrustum();
	void updatePosition();
	void updateOrientation();
	void updateView();
	void updateProjection();
public:
	Camera();

	void update();
	void hookPlayer(Player* player);
	bool isAABBInFrustum(const AABB& aabb);

	const Orientation& getOrientation() { return orientation; }
	glm::mat4& getView() { return view; }
	glm::mat4& getProjView() { return projView; }
	glm::mat4& getProjection() { return projection; }
	glm::mat4& getSkyboxProjView() { return skyboxProjView; }
};

#endif