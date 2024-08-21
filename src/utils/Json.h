#ifndef JSON_H
#define JSON_H

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Files.h"

class Json {
public:
	static nlohmann::json parse(const std::string& path);
	static void save(const std::string& path, const nlohmann::json& json);
	static glm::vec4 toVec4(const nlohmann::basic_json<>& arr);
	static glm::vec3 toVec3(const nlohmann::basic_json<>& arr);
	static glm::vec2 toVec2(const nlohmann::basic_json<>& arr);
};

#endif