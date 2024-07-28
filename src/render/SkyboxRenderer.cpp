#include "SkyboxRenderer.h"

#include "../textures/TextureManager.h"
#include "../world/WorldConstants.h"
#include "Renderer.h"

SkyboxRenderer::SkyboxRenderer() {
	shader = new Shader("shaders/skybox.vs", "shaders/skybox.fs");
    matModel = glm::mat4(1);

	loadTexture();
	makeModel();
}

SkyboxRenderer::~SkyboxRenderer() {
	model.reset();

	delete shader;
	delete texture;
}

void SkyboxRenderer::setTime(float time) {
    float angle = time * 360.0f / DAYCYCLE_TICKS;

    matModel = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1, 0, 0));
}

void SkyboxRenderer::render(Camera& camera) {
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
    
	shader->use();

	TextureManager::bindTexture(*texture, *shader, "skybox", 0);

	shader->setMat4("model", matModel);
	shader->setMat4("view", glm::mat4(glm::mat3(camera.getView())));
	shader->setMat4("projection", camera.getProjection());
	
	Renderer::drawElements(model.getRenderInfo());

	glDepthMask(GL_TRUE);
}

void SkyboxRenderer::loadTexture() {
	std::array<const char*, 6> files{
		"resources/textures/skybox/right.jpg", 
		"resources/textures/skybox/left.jpg", 
		"resources/textures/skybox/top.jpg",
		"resources/textures/skybox/bottom.jpg",
		"resources/textures/skybox/front.jpg", 
		"resources/textures/skybox/back.jpg"
	};

	texture = new CubeTexture(files, false);
}

void SkyboxRenderer::makeModel() {
	Mesh mesh;
	
	mesh.vertexPositions = {  
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

	model.addMesh(mesh);
}