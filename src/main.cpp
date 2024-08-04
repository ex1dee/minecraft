#include <glad/glad.c>

#include <iostream>

#include "window/Window.h"
#include "window/Events.h"
#include "config/Config.h"
#include "shaders/ShadersDatabase.h"
#include "entity/EntitiesDatabase.h"
#include "world/block/BlocksDatabase.h"
#include "world/World.h"
#include "render/ChunkRenderer.h"
#include "states/PlayState.h"
#include "states/BaseState.h"

#include "player/Camera.h"
#include "shaders/Shader.h"
#include "render/model/Model.h"
#include "render/Renderer.h"
#include <vector>
#include "textures/BasicTexture.h"
#include "textures/TextureManager.h"
#include "textures/TextureAtlas.h"

#include "utils/VecMap.h"

int main() {
    try {
        Config::initialize();
        Window::initialize();
        BlocksDatabase::initialize();
        EntitiesDatabase::initialize();
        ShadersDatabase::initialize();
    } catch (const char* message) {
        std::cout << "ERROR::INITIALIZE\n" << message << "\n";
        glfwTerminate();

        return -1;
    }

    Camera camera;

    Renderer renderer;
    Player player(&camera);

    std::vector<BaseState*> states;
    states.push_back(new PlayState(&renderer, &player, &camera));

    while (!Window::shouldClose()) {
        camera.update();

        for (BaseState* state : states) {
            state->handleInput();
            state->update();
            state->render();
        }

        Window::swapBuffers();
        Events::pollEvents();
    }

    for (BaseState* state : states) {
        delete state;
    }

    Window::finalize();
    BlocksDatabase::finalize();
    EntitiesDatabase::finalize();
    ShadersDatabase::finalize();
}