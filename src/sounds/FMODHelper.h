#ifndef FMODHELPER_H
#define FMODHELPER_H

#include <fmod/fmod.h>
#include <fmod/fmod_errors.h>
#include <glm/glm.hpp>

class FMODHelper {
public:
    static FMOD_RESULT checkError(FMOD_RESULT result);
    static FMOD_VECTOR getFMODVector(const glm::vec3& glmVec);
};

#endif