#ifndef JSON_H
#define JSON_H

#include <nlohmann/json.hpp>
#include <string>

#include "Files.h"

class Json {
public:
	static nlohmann::json parse(const char* path);
	static void save(const char* path, nlohmann::json json);
};

#endif