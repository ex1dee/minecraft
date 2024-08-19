#ifndef TEXT2D_H
#define TEXT2D_H

#include <vector>
#include <string>

#include "../render/sprite/Sprite.h"
#include "TextAlignment.h"
#include "FTLoader.h"

class Text2D {
	std::vector<Sprite*> sprites;
	TextAlignment alignment;
	Transform transform;
	std::wstring text;
	glm::vec4 color;

	std::vector<std::wstring> lines;
	float maxWidth;
	float height;

	void calcMaxWidth();
	void calcHeight();
	std::vector<std::wstring> getLines();
	std::vector<float> getAlignmentOffsets();
	float getAlignmentOffset(const std::wstring& line);
	float getWidth(const std::wstring& line, int length = INT_MAX);
	int getHeight(const std::wstring& line, int length = INT_MAX);
	Sprite* createSprite(const FTCharacter& ftChar, float x, float y);
public:
	Text2D() = default;
	Text2D(const std::wstring& text, TextAlignment alignment, const Transform& transform, const glm::vec4& color = glm::vec4(1));
	Text2D(const Text2D& other);

	float getHeight() { return height; }
	float getMaxWidth() { return maxWidth; }
	const std::wstring& getText() { return text; }
	const glm::vec3& getPosition() { return transform.position; }
	const glm::vec3& getScale() { return transform.scale; }

	void reset();
	void draw(Shader& activeShader);
	void setText(const std::wstring& text);
	void setColor(const glm::vec4& color);
	void setPosition(const glm::vec3& position);
	void setScale(const glm::vec3& scale);
};

#endif