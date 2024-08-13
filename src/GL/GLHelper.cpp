#include "GLHelper.h"

void GLHelper::checkGLError() {
    GLenum error = glGetError();

    while (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << getGLErrorString(error) << "\n";

        error = glGetError();
    }
}

const char* GLHelper::getGLErrorString(GLenum error) {
    switch (error) {
    case GL_NO_ERROR:
        return "No error";
    case GL_INVALID_ENUM:
        return "Invalid enum";
    case GL_INVALID_VALUE:
        return "Invalid value";
    case GL_INVALID_OPERATION:
        return "Invalid operation";
    case GL_OUT_OF_MEMORY:
        return "Out of memory";
    default:
        return "Unknown error";
    }
}