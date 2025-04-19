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

	template<typename T>
	void addVBO(int dimensions, const std::vector<T> vertices, int index, GLenum type) {
		addVBO(dimensions, vertices.data(), vertices.size(), index, type);
	}

	template<typename T>
	void addVBO(int dimensions, const T* vertices, int size, int index, GLenum type) {
		if (size == 0)
			return;

		uint32_t VBO;
		GL(glGenBuffers(1, &VBO));
		GL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
		GL(glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), vertices, GL_STATIC_DRAW));

		if (type == GL_INT) {
			GL(glVertexAttribIPointer(index, dimensions, type, 0, 0));
		} else {
			GL(glVertexAttribPointer(index, dimensions, type, false, 0, 0));
		}

		GL(glEnableVertexAttribArray(index));

		buffers.push_back(VBO);
	}
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

#endif