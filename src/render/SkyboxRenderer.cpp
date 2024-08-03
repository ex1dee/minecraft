#include "SkyboxRenderer.h"

#include "../textures/TextureManager.h"
#include "../world/WorldConstants.h"
#include "Renderer.h"

SkyboxRenderer::SkyboxRenderer() {
	skyboxShader = new Shader("shaders/skybox.vs", "shaders/skybox.fs");

	loadTexture();
	makeModel();
}

SkyboxRenderer::~SkyboxRenderer() {
	model.reset();

	delete skyboxShader;
	delete texture;
}

void SkyboxRenderer::render(Camera* camera, const Sun& sun) {
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
    
	skyboxShader->use();

    TextureManager::bindTexture(*texture, *skyboxShader, "background");

    skyboxShader->setMat4("projView", camera->getSkyboxProjView());
    skyboxShader->setVec3("lightDir", sun.getLight().direction);
	
    model.draw(skyboxShader);

	glDepthMask(GL_TRUE);
}

void SkyboxRenderer::loadTexture() {
	std::array<const char*, 6> files{
		"resources/textures/skybox/stars.jpg", 
        "resources/textures/skybox/stars.jpg",
        "resources/textures/skybox/stars.jpg",
        "resources/textures/skybox/stars.jpg",
        "resources/textures/skybox/stars.jpg",
        "resources/textures/skybox/stars.jpg"
	};

	texture = new CubeTexture(files, false);
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