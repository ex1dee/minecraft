#include "Json.h"

nlohmann::json Json::parse(const char* path) {
	std::string data = Files::read(path);
	nlohmann::json json = nlohmann::json::parse(data);
	
	return json;
}

void Json::save(const char* path, nlohmann::json json) {
	std::string data = json.dump();
	Files::write(path, data);
}

glm::vec3 Json::toVec3(const nlohmann::basic_json<>& arr) {
	return glm::vec3(
		arr[0],
		arr[1],
		arr[2]
	);
}