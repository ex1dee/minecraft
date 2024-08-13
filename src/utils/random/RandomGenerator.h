#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "BaseRandomGenerator.h"

constexpr uint32_t SEED_CONSTANT = 1812433253U;

class RandomGenerator : public BaseRandomGenerator { // XORshift
public:
    RandomGenerator(const uint32_t& seed = time(0)) {
        setSeed(seed);
    }

    uint32_t getSeed() {
        return x;
    }

    void setSeed(const uint32_t& seed) {
        x = seed;
        y = x * SEED_CONSTANT + 1;
        z = y * SEED_CONSTANT + 1;
        w = z * SEED_CONSTANT + 1;
    }

    uint32_t generateUInt() {
        uint32_t t = x ^ (x << 11);

        x = y;
        y = z;
        z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));

        return w;
    }
private:
    uint32_t x, y, z, w;
};

#endif