#include <glad/glad.c>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window/Window.h"
#include "window/Events.h"
#include "config/Config.h"
#include "world/block/BlocksDatabase.h"
#include "world/World.h"
#include "render/ChunkRenderer.h"
#include "states/PlayState.h"
#include "states/BaseState.h"

#include "player/Camera.h"
#include "shaders/Shader.h"
#include "render/Model.h"
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
        Events::initialize();
        BlocksDatabase::initialize();
    } catch (const char* message) {
        std::cout << "ERROR::INITIALIZE\n" << message << "\n";
        glfwTerminate();

        return -1;
    }
    
    Camera camera;
    camera.update();

    Renderer renderer;
    Player player;

    std::vector<BaseState*> states;
    states.push_back(new PlayState(&renderer, &player, &camera));

    while (!Window::shouldClose()) {
        camera.update();

        for (BaseState* state : states) {
            state->handleInput();
            state->update();
            state->render();
        }

        renderer.finishRender(player, camera);

        Window::swapBuffers();
        Events::pollEvents();
    }

    for (BaseState* state : states) {
        delete state;
    }

    Window::finalize();
    BlocksDatabase::finalize();
}