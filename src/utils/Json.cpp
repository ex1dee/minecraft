#include "Json.h"

nlohmann::json Json::parse(const char* path) {
	std::string data = Files::read(path);
	nlohmann::json json = nlohmann::json::parse(data);
	
	return json;
}

void Json::save(const char* path, const nlohmann::json& json) {
	Files::write(path, json.dump());
}

glm::vec4 Json::toVec4(const nlohmann::basic_json<>& arr) {
	return glm::vec4(
		arr[0],
		arr[1],
		arr[2],
		arr[3]
	);
}

glm::vec3 Json::toVec3(const nlohmann::basic_json<>& arr) {
	return glm::vec3(
		arr[0],
		arr[1],
		arr[2]
	);
}

glm::vec2 Json::toVec2(const nlohmann::basic_json<>& arr) {
	return glm::vec2(
		arr[0],
		arr[1]
	);
}