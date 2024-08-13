#include "ShadersDatabase.h"

std::unordered_map<ShaderType, Shader*> ShadersDatabase::shaders;

void ShadersDatabase::initialize() {
	shaders[ShaderType::DEFAULT]	 = new Shader("shaders/default.vs", "shaders/default.fs");
	shaders[ShaderType::FRAMEBUFFER] = new Shader("shaders/framebuffer.vs", "shaders/framebuffer.fs");
	shaders[ShaderType::SKYBOX]		 = new Shader("shaders/skybox.vs", "shaders/skybox.fs");
	shaders[ShaderType::LINE]	     = new Shader("shaders/line.vs", "shaders/line.fs");
	shaders[ShaderType::SPRITE]		 = new Shader("shaders/sprite.vs", "shaders/sprite.fs");
	shaders[ShaderType::CLOUDS]		 = new Shader("shaders/sprite.vs", "shaders/clouds.fs");
}

void ShadersDatabase::finalize() {
	for (std::pair<ShaderType, Shader*> pair : shaders) {
		delete pair.second;
	}
}