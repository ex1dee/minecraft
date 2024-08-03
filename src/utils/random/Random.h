#ifndef RANDOM_H
#define RANDOM_H

#include "RandomGenerator.h"

inline float rangedRand(RandomGenerator& randGen, float min, float max) {
    if (max < min) {
        std::swap(min, max);
    } else if (max == min) {
        return min;
    }

    return randGen.generateFloat() * (max - min) + min;
}

inline int rangedRand(RandomGenerator& randGen, int min, int max) {
    if (max < min) {
        std::swap(min, max);
    } else if (max == min) {
        return min;
    }

    return randGen.generateUInt() % (max - min) + min;
}

#endif