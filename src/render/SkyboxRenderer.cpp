#include "SkyboxRenderer.h"

#include "../textures/TextureManager.h"
#include "../world/WorldConstants.h"
#include "../shaders/ShadersDatabase.h"
#include "Renderer.h"

SkyboxRenderer::SkyboxRenderer() {
	loadTexture();
	makeModel();
}

void SkyboxRenderer::render(const Camera& camera, const Sun& sun, const Fog& fog) {
    Shader* skyboxShader = &ShadersDatabase::get(ShaderType::SKYBOX);
	skyboxShader->use();

    skyboxShader->setMat4("projection", camera.getProjection());
    skyboxShader->setMat4("view", camera.getSkyboxView());
    skyboxShader->setVec3("lightDir", sun.getLight().direction);
	
    fog.addToShader(skyboxShader);

    TextureManager::bindTexture(*texture, *skyboxShader, "background");

    model.draw(*skyboxShader);
}

void SkyboxRenderer::loadTexture() {
	std::array<std::string, 6> files{
		"stars.jpg", 
        "stars.jpg",
        "stars.jpg",
        "stars.jpg",
        "stars.jpg",
        "stars.jpg"
	};

    texture = TextureLoader::loadCube("resources/textures/skybox", files, false);
}

void SkyboxRenderer::makeModel() {
    std::unique_ptr<MeshData> meshData = std::make_unique<MeshData>(MeshType::CUBE, 3);
	
	meshData->vertexPositions = {
        // right
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        // left
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        // top
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        
        // back
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        // front
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        // bottom
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

	model.addMesh(meshData);
}