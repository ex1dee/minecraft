#include "ShadersDatabase.h"

std::unordered_map<ShaderType, Shader*> ShadersDatabase::shaders;

void ShadersDatabase::initialize() {
	shaders[DEFAULT]	 = new Shader("shaders/default.vs", "shaders/default.fs");
	shaders[FRAMEBUFFER] = new Shader("shaders/framebuffer.vs", "shaders/framebuffer.fs");
	shaders[SKYBOX]		 = new Shader("shaders/skybox.vs", "shaders/skybox.fs");
}

void ShadersDatabase::finalize() {
	for (std::pair<ShaderType, Shader*> pair : shaders) {
		delete pair.second;
	}
}