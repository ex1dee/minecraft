#ifndef CONFIG_H
#define CONFIG_H

#include "../utils/Json.h"

class Config {
public:
	static nlohmann::json settings;
	static nlohmann::json config;

	static void initialize();
};

#endif