#ifndef KEYROTATION_H
#define KEYROTATION_H

#include "AnimationKey.h"

class KeyRotation : public AnimationKey {
public:
	glm::quat rotation;
};

#endif