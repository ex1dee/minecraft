#include "Window.h"
#include "Events.h"
#include <iostream>

#include "../config/Config.h"

GLFWwindow* Window::window = nullptr;
int Window::width;
int Window::height;

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

void Window::initialize() {
    if (!glfwInit()) {
        throw "Failed to initialize GLFW";
    }
    
    createWindow();
    setCallbacks();
    gladLoad();

    glfwSetWindowPos(window, width / 2, height / 2);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::finalize() {
    glfwTerminate();
}

void Window::createWindow() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::string title = Config::config["window"]["title"];
    width = Config::config["window"]["width"];
    height = Config::config["window"]["height"];

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    
    if (window == NULL) {
        throw "Failed to create GLFW window";
    }

    glfwMakeContextCurrent(window);
}

void Window::setCallbacks() {
    glfwSetKeyCallback(window, Events::keyCallback);
    glfwSetMouseButtonCallback(window, Events::mouseButtonCallback);
    glfwSetCursorPosCallback(window, Events::cursorPosCallback);
    glfwSetFramebufferSizeCallback(window, Events::framebufferSizeCallback);
}

void Window::gladLoad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw "Failed to initialize GLAD";
    }
}