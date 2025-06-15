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
	void addEBO(const std::vector<uint32_t>& indices);

	template<typename T> void addVBO(int dimensions, const std::vector<T> vertices, int index, GLenum type);
	template<typename T> void addVBO(int dimensions, const T* vertices, int size, int index, GLenum type);
public:
	Drawable() = default;
	virtual ~Drawable();

	Drawable(const Drawable& other);

	virtual void setup();
	virtual void reset();
	virtual void draw(Shader& shader) = 0;

	void resetBuffers();

	uint32_t getVAO() { return VAO; }
};

#include "Drawable.inl"

#endif