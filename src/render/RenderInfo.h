#ifndef RENDERINFO_H
#define RENDERINFO_H

class RenderInfo {
public:
	unsigned int VAO;
	int indicesCount;
	int vertexCount;

	void reset() {
		VAO = 0;
		indicesCount = 0;
		vertexCount = 0;
	}
};

#endif