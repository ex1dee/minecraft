#ifndef SHADERSDATABASE_H
#define SHADERSDATABASE_H

#include <unordered_map>

#include "ShaderType.h"
#include "Shader.h"

class ShadersDatabase {
	static std::unordered_map<ShaderType, std::shared_ptr<Shader>> shaders;
public:
	static void initialize();

	static Shader& get(ShaderType type) {
		return *shaders[type];
	}
};

#endif