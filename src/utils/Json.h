#ifndef JSON_H
#define JSON_H

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Files.h"

class Json {
public:
	static nlohmann::json parse(const char* path);
	static void save(const char* path, nlohmann::json json);
	static glm::vec3 toVec3(const nlohmann::basic_json<>& arr);
};

#endif