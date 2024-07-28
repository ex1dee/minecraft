#ifndef BASERANDOMGENERATOR_H
#define BASERANDOMGENERATOR_H

#include <climits>
#include <cstdint>
#include <time.h>

#define SEED_CONSTANT 1812433253U

class BaseRandomGenerator {
public:
    BaseRandomGenerator() {}

    virtual uint32_t getSeed() = 0;
    virtual uint32_t generateUInt() = 0;
    virtual void setSeed(const uint32_t& seed) = 0;

    inline float generateFloat() {
        return toFloat(generateUInt());
    }

    inline float generateSignedFloat() { // between -1.0f and 1.0f
        return toFloat(generateUInt()) * 2.0f - 1.0f;
    }

    inline uint8_t generateByte() {
        return toByte(generateUInt());
    }

    inline int toInt(const uint32_t& value) {
        return value - INT_MAX;
    }

    inline uint8_t toByte(const uint32_t& value) {
        return static_cast<uint8_t>(value >> (23 - 8));
    }

    inline float toFloat(const uint32_t& value) {
        return (static_cast<float>(value & 0x007FFFFF)) / 0x007FFFFF;
    }
};

#endif