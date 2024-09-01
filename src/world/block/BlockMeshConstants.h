#ifndef BLOCKMESHCONSTANTS_H
#define BLOCKMESHCONSTANTS_H

#include <glm/glm.hpp>
#include <array>

constexpr std::array<float, 12> frontFace{ 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, };
constexpr std::array<float, 12> backFace{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, };
constexpr std::array<float, 12> leftFace{ 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, };
constexpr std::array<float, 12> rightFace{ 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, };
constexpr std::array<float, 12> topFace{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, };
constexpr std::array<float, 12> bottomFace{ 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 };

constexpr std::array<float, 12> xSide1{ 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, };
constexpr std::array<float, 12> xSide2{ 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, };

constexpr glm::vec3 frontFaceNormal{ 0, 0, 1 };
constexpr glm::vec3 backFaceNormal{ 0, 0, -1 };
constexpr glm::vec3 leftFaceNormal{ -1, 0, 0 };
constexpr glm::vec3 rightFaceNormal{ 1, 0, 0 };
constexpr glm::vec3 topFaceNormal{ 0, 1, 0 };
constexpr const glm::vec3 bottomFaceNormal{ 0, -1, 0 };

#endif