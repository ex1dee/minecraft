#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../math/Frustum.h"
#include "Player.h"

#define CAMERA_NEAR 0.1f
#define CAMERA_FAR 100.0f

class Camera {
	glm::mat4 view;
	glm::mat4 projView;
	glm::mat4 projection;
	Frustum frustum;
	float aspect;
	float fov;
	float yaw;
	float pitch;
	Player* player;

	void updateFrustum();
	void updatePosition();
	void updateOrientation();
	void updateView();
	void updateProjection();
public:
	Transform* transform;

	Camera();
	~Camera();

	void update();
	void hookPlayer(Player& player);
	bool isAABBInFrustum(AABB& aabb);
	glm::mat4& getView();
	glm::mat4& getProjection();
};

#endif