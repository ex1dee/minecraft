#include "FMODHelper.h"

#include <iostream>

FMOD_RESULT FMODHelper::checkError(FMOD_RESULT result) {
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << "\n";
    }

    return result;
}

FMOD_VECTOR FMODHelper::getFMODVector(const glm::vec3& glmVec) {
    FMOD_VECTOR v;

    v.x = glmVec.x;
    v.y = glmVec.y;
    v.z = glmVec.z;

    return v;
}