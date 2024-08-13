#include "Window.h"

#include <iostream>

#include "../config/Config.h"
#include "../input/Input.h"
#include "../gui/GUI.h"

GLFWmonitor* Window::monitor;
GLFWwindow* Window::window;
bool Window::fullscreen = false;
int Window::prevWidth = 0;
int Window::prevHeight = 0;
int Window::screenWidth;
int Window::screenHeight;
int Window::width;
int Window::height;

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
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

    monitor = glfwGetPrimaryMonitor();

    setupScreenSize();
    setupDefaultWindowSize();

    std::string title = Config::config["window"]["title"];

    window = glfwCreateWindow(width, height, title.c_str(), 0, nullptr);
    
    if (window == NULL) {
        throw "Failed to create GLFW window";
    }

    glfwMakeContextCurrent(window);
    setupAntiAliasing();
}

void Window::setupScreenSize() {
    const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

    screenWidth = vidmode->width;
    screenHeight = vidmode->height;
}

void Window::setupDefaultWindowSize() {
    width = screenWidth * 0.5f;
    height = screenHeight * 0.5f;
}

void Window::setupAntiAliasing() {
    int aax = Config::config["anti_aliasing"];
    glfwWindowHint(GLFW_SAMPLES, aax);
}

void Window::setCallbacks() {
    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
    glfwSetCursorPosCallback(window, Input::cursorPosCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void Window::gladLoad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw "Failed to initialize GLAD";
    }
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Window::width = width;
    Window::height = height;
    Window::setWindowViewport();
    
    GUI::framebufferSizeCallback(window, width, height);
}

void Window::setWindowViewport() {
    GL(glViewport(0, 0, width, height));
}

void Window::toggleFullscreen() {
    fullscreen = !fullscreen;

    if (fullscreen) {
        prevWidth = width;
        prevHeight = height;
        
        glfwSetWindowMonitor(window, monitor, 0, 0, screenWidth, screenHeight, GLFW_DONT_CARE);
    } else {
        int width, height;

        if (prevWidth != 0) {
            width = prevWidth;
            height = prevHeight;
        } else {
            setupDefaultWindowSize();
        }

        int xpos = (screenWidth - width) * 0.5f;
        int ypos = (screenHeight - height) * 0.5f;

        glfwSetWindowMonitor(window, NULL, xpos, ypos, prevWidth, prevHeight, GLFW_DONT_CARE);
    }
}