#include "ShadersDatabase.h"

std::unordered_map<ShaderType, std::shared_ptr<Shader>> ShadersDatabase::shaders;

void ShadersDatabase::initialize() {
	shaders[ShaderType::DEFAULT]	 = std::make_shared<Shader>("shaders/default.vs", "shaders/default.fs");
	shaders[ShaderType::FRAMEBUFFER] = std::make_shared<Shader>("shaders/framebuffer.vs", "shaders/framebuffer.fs");
	shaders[ShaderType::SKYBOX]		 = std::make_shared<Shader>("shaders/skybox.vs", "shaders/skybox.fs");
	shaders[ShaderType::LINE]	     = std::make_shared<Shader>("shaders/line.vs", "shaders/line.fs");
	shaders[ShaderType::SPRITE]		 = std::make_shared<Shader>("shaders/sprite.vs", "shaders/sprite.fs");
	shaders[ShaderType::CLOUDS]		 = std::make_shared<Shader>("shaders/sprite.vs", "shaders/clouds.fs");
	shaders[ShaderType::TEXT]		 = std::make_shared<Shader>("shaders/sprite.vs", "shaders/text.fs");
}