#ifndef W3DATTRIBUTES_H
#define W3DATTRIBUTES_H

#include "FMODHelper.h"

class W3DAttributes {
public:
	FMOD_VECTOR position;
	FMOD_VECTOR velocity;
	FMOD_VECTOR forward;
	FMOD_VECTOR up;

	W3DAttributes() {}

	W3DAttributes(
		const glm::vec3& position,
		const glm::vec3& velocity = glm::vec3(0.0f),
		const glm::vec3& forward = glm::vec3(0.0f),
		const glm::vec3& up = glm::vec3(0.0f)
	) {
		update(position, velocity, forward, up);
	}

	W3DAttributes(
		const FMOD_VECTOR& position,
		const FMOD_VECTOR& velocity,
		const FMOD_VECTOR& forward,
		const FMOD_VECTOR& up
	) : position(position), velocity(velocity), forward(forward), up(up) {

	}

	void update(
		const glm::vec3& position,
		const glm::vec3& velocity = glm::vec3(0.0f),
		const glm::vec3& forward = glm::vec3(0.0f),
		const glm::vec3& up = glm::vec3(0.0f)) {

		this->position = FMODHelper::getFMODVector(position);
		this->velocity = FMODHelper::getFMODVector(velocity);
		this->forward = FMODHelper::getFMODVector(forward);
		this->up = FMODHelper::getFMODVector(up);
	}
};

#endif