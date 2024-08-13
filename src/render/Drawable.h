#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glad/glad.h>
#include <vector>

#include "../shaders/Shader.h"

class Drawable {
protected:
	uint32_t VAO, EBO;

	std::vector<uint32_t> buffers;

	void genVAO();
	void addVBO(int dimensions, const std::vector<float>& vertices);
	void addEBO(const std::vector<uint32_t>& indices);
public:
	virtual void setup();
	virtual void reset() = 0;
	virtual void draw(Shader* shader) = 0;

	void resetBuffers();
};

#endif