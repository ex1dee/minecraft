#ifndef RANDOM_H
#define RANDOM_H

#include "RandomGenerator.h"

inline float rangedRand(RandomGenerator& randGen, float min, float max) { // min <= x <= max
    if (max < min) {
        float t = min;
        min = max;
        max = t;
    } else if (max == min) {
        return min;
    }

    return randGen.generateFloat() * (max - min) + min;
}

inline int rangedRand(RandomGenerator& randGen, int min, int max) { // min <= x <= max
    if (max < min) {
        int t = min;
        min = max;
        max = t;
    } else if (max == min) {
        return min;
    }

    return randGen.generateUInt() % (max - min + 1) + min;
}

#endif