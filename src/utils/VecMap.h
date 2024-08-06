#ifndef VECMAP_H
#define VECMAP_H

#include <unordered_map>
#include <functional>
#include <glm/glm.hpp>
#include <map>

struct Vec2Hash {
	std::size_t operator()(const glm::vec2& vec) const {
		return std::hash<float>()(vec.x) ^ std::hash<float>()(vec.y);
	}
};

struct Vec2Equal {
	bool operator()(const glm::vec2& vec1, const glm::vec2& vec2) const {
		return (vec1.x == vec2.x) && (vec1.y == vec2.y);
	}
};

struct Vec3Hash {
	std::size_t operator()(const glm::vec3& vec) const {
		return std::hash<float>()(vec.x) ^ std::hash<float>()(vec.y) ^ std::hash<float>()(vec.z);
	}
};

struct Vec3Equal {
	bool operator()(const glm::vec3& vec1, const glm::vec3& vec2) const {
		return (vec1.x == vec2.x) && (vec1.y == vec2.y) && (vec1.z == vec2.z);
	}
};

#endif