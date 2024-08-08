#include "SkyboxRenderer.h"

#include "../textures/TextureManager.h"
#include "../world/WorldConstants.h"
#include "../shaders/ShadersDatabase.h"
#include "Renderer.h"

SkyboxRenderer::SkyboxRenderer() {
	loadTexture();
	makeModel();
}

SkyboxRenderer::~SkyboxRenderer() {
	model.reset();

	delete texture;
}

void SkyboxRenderer::render(Camera* camera, const Sun& sun) {    
    Shader* skyboxShader = ShadersDatabase::get(ShaderType::SKYBOX);
	skyboxShader->use();

    TextureManager::bindTexture(*texture, *skyboxShader, "background");

    skyboxShader->setMat4("projView", camera->getSkyboxProjView());
    skyboxShader->setVec3("lightDir", sun.getLight().direction);
	
    model.draw(skyboxShader);
}

void SkyboxRenderer::loadTexture() {
	std::array<const char*, 6> files{
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
	MeshData meshData(CUBE, 3);
	
	meshData.vertexPositions = {
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