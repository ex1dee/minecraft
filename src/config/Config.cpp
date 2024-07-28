#include "Config.h"

#include <iostream>

nlohmann::json Config::settings;
nlohmann::json Config::config;

void Config::initialize() {
	try {
		settings = Json::parse("config/settings.json");
		config = Json::parse("config/config.json");
	} catch (std::ios_base::failure e) {
		std::cout << "ERROR::CONFIG::PARSE\n" << e.what() << "\n";
	}
}