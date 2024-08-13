#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Orientation {
	glm::mat4 rotation;
	float yaw;
	float pitch;
public:
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	void update(float yaw, float pitch);
	void update(const glm::vec3& front);

	float getYaw() const { return yaw; }
	float getPitch() const { return pitch; }
	const glm::mat4& getRotation() const { return rotation; }
	glm::vec3 getMovingFront() const { return glm::normalize(glm::vec3(front.x, 0, front.z)); }
	glm::vec3 getMovingRight() const { return glm::normalize(glm::vec3(right.x, 0, right.z)); }
};

#endif