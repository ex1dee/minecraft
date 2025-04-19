#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Orientation {
	float yaw;
	float pitch;

	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
public:
	Orientation() = default;

	void update(float yaw, float pitch);
	void update(const glm::vec3& front);

	float getYaw() const { return yaw; }
	float getPitch() const { return pitch; }
	const glm::vec3& getUp() const { return up; }
	const glm::vec3& getRight() const { return right; }
	const glm::vec3& getFront() const { return front; }
	const glm::vec3& getMovingFront() const { return glm::normalize(glm::vec3(front.x, 0, front.z)); }
	const glm::vec3& getMovingRight() const { return glm::normalize(glm::vec3(right.x, 0, right.z)); }
};

#endif