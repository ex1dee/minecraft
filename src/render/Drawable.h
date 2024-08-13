#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../GL/GLHelper.h"
#include <vector>

#include "../shaders/Shader.h"

class Drawable {
protected:
	std::vector<uint32_t> buffers;
	uint32_t VAO, EBO;

	void genVAO();
	void addVBO(int dimensions, const std::vector<float>& vertices);
	void addEBO(const std::vector<uint32_t>& indices);
public:
	~Drawable();

	virtual void setup();
	virtual void reset() = 0;
	virtual void draw(Shader& shader) = 0;

	void resetBuffers();
};

#endif