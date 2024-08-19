#ifndef GLHELPER_H
#define GLHELPER_H

#include <glad/glad.h>
#include <iostream>
#include <assert.h>

#define GL(line) {line; assert(glGetError() == GL_NO_ERROR);}

class GLHelper {
public:
    static void checkGLError();
    static const char* getGLErrorString(GLenum error);
};

#endif