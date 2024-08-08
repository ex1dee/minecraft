#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glad/glad.h>
#include <vector>

#include "../shaders/Shader.h"

class Drawable {
protected:
	unsigned int VAO, VBO, EBO;

	std::vector<unsigned int> buffers;

	void genVAO();
	void addVBO(int dimensions, const std::vector<float>& vertices);
	void addEBO(const std::vector<unsigned int>& indices);
public:
	virtual void setup();
	virtual void reset() = 0;
	virtual void draw(Shader* shader) = 0;

	void resetBuffers();
};

#endif