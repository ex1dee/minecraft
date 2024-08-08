#ifndef ATLASCOORDS_H
#define ATLASCOORDS_H

#include <glm/glm.hpp>
#include <vector>
#include <array>

class AtlasCoords {
public:
	bool exactly;
	glm::vec2 bottomLeft;
	glm::vec2 topRight;

	AtlasCoords() {}

	AtlasCoords(bool exactly, float xMin, float xMax, float yMin, float yMax)
		: exactly(exactly), bottomLeft(xMin, yMin), topRight(xMax, yMax) {
		AtlasCoords(exactly, bottomLeft, topRight);
	}

	AtlasCoords(bool exactly, const glm::vec2& bottomLeft, const glm::vec2& topRight)
		: exactly(exactly), bottomLeft(bottomLeft), topRight(topRight) {}

	void addToTexCoords(std::vector<float>& texCoords) const {
		std::array<float, 8> arr = toArray();

		texCoords.insert(texCoords.end(), arr.begin(), arr.end());
	}

	std::array<float, 8> toArray() const {
		return {
			bottomLeft.x, bottomLeft.y,
			topRight.x, bottomLeft.y,
			topRight.x, topRight.y,
			bottomLeft.x, topRight.y
		};
	}
};

#endif