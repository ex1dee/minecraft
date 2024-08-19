#include <glad/glad.c>

#include <iostream>

#include "window/Window.h"
#include "input/Input.h"
#include "config/Config.h"
#include "shaders/ShadersDatabase.h"
#include "entity/EntitiesDatabase.h"
#include "world/block/BlocksDatabase.h"
#include "items/ItemsDatabase.h"
#include "text/FTLoader.h"
#include "gui/GUIDatabase.h"
#include "gui/GUI.h"

#include "states/PlayState.h"
#include "player/Camera.h"

#include <ft2build.h>

int main() {
    try {
        Config::initialize();
        Window::initialize();
        BlocksDatabase::initialize();
        EntitiesDatabase::initialize();
        ShadersDatabase::initialize();
        GUIDatabase::initialize();
        ItemsDatabase::initialize();
        FTLoader::initialize();
        GUI::initialize();
    } catch (const char* message) {
        std::cout << "ERROR::INITIALIZE\n" << message << "\n";
        glfwTerminate();

        return -1;
    }

    Camera camera;
    Player player(camera);

    std::vector<BaseState*> states;
    states.push_back(new PlayState(player));

    player.getBackpackView().setItem(0, 0, ItemStack(GRASS_BLOCK));
    player.getBackpackView().setItem(3, 1, ItemStack(GRASS_BLOCK));

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
        freePointer(&state);
    }

    Window::finalize();
    BlocksDatabase::finalize();
    EntitiesDatabase::finalize();
    ShadersDatabase::finalize();
    GUIDatabase::finalize();
    ItemsDatabase::finalize();
    FTLoader::finalize();
}