#include <glad/glad.c>

#include <iostream>

#include "window/Window.h"
#include "input/Input.h"
#include "config/Config.h"
#include "shaders/ShadersDatabase.h"
#include "entity/EntitiesDatabase.h"
#include "world/block/BlocksDatabase.h"
#include "states/PlayState.h"
#include "player/Camera.h"
#include "gui/GUIDatabase.h"
#include "gui/GUI.h"

#include "../dependencies/stb_image.h"

int main() {
    try {
        Config::initialize();
        Window::initialize();
        BlocksDatabase::initialize();
        EntitiesDatabase::initialize();
        ShadersDatabase::initialize();
        GUIDatabase::initialize();
        GUI::initialize();
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
        Input::pollEvents();
    }

    for (BaseState* state : states) {
        delete state;
    }

    Window::finalize();
    BlocksDatabase::finalize();
    EntitiesDatabase::finalize();
    ShadersDatabase::finalize();
    GUIDatabase::finalize();
}