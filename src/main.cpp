#include <glad/glad.c>

#include <iostream>

#include "window/Window.h"
#include "input/Input.h"
#include "config/Config.h"
#include "text/FTLoader.h"
#include "shaders/ShadersDatabase.h"
#include "entity/EntitiesDatabase.h"
#include "world/block/BlocksDatabase.h"
#include "sounds/SoundsDatabase.h"
#include "items/ItemsDatabase.h"
#include "sounds/SoundEngine.h"
#include "gui/GUIDatabase.h"
#include "gui/GUI.h"

#include "PlayState.h"

int main() {
    try {
        Config::initialize();
        Window::initialize();
        SoundEngine::initialize();

        SoundsDatabase::initialize();
        BlocksDatabase::initialize();
        EntitiesDatabase::initialize();
        ShadersDatabase::initialize();
        GUIDatabase::initialize();
        ItemsDatabase::initialize();

        FTLoader::initialize();
        GUI::initialize();
    } catch (...) {
        glfwTerminate();

        return -1;
    }

    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::shared_ptr<Player> player = std::make_shared<Player>(camera);

    PlayState state(player);

    // 

    player->getHotbarView().setItem(0, 0, ItemStack(STICK, 32));
    player->getHotbarView().setItem(1, 0, ItemStack(GRASS_BLOCK, 32));

    // 

    glfwSetTime(0);

    while (!Window::shouldClose()) {
        camera->update();

        state.handleInput();
        state.update();
        state.render();

        if (Input::justPressed(GLFW_KEY_ESCAPE))
            break;

        Window::swapBuffers();
        Input::pollEvents();
    }

    Window::finalize();
    FTLoader::finalize();
    SoundEngine::finalize();
}