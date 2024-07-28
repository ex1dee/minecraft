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