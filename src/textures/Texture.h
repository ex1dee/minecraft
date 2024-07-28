#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture {
protected:
	unsigned int ID;
	GLenum type;
public:
	unsigned int getID() {
		return ID;
	}

	GLenum getType() {
		return type;
	}
};

#endif