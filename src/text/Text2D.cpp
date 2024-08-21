#include "Text2D.h"

constexpr float LINE_SPACING = 10.0f;

Text2D::Text2D(const std::wstring& text, TextAlignment alignment, const Transform& transform, const glm::vec4& color)
	: transform(transform), color(color), alignment(alignment) {
	setText(text);
}

Text2D::Text2D(const Text2D& other) {
	text = other.text;
	alignment = other.alignment;
	transform = other.transform;
	color = other.color;

	for (const std::unique_ptr<Sprite>& sprite : other.sprites) {
		sprites.push_back(std::make_unique<Sprite>(*sprite));
	}
}

void Text2D::setText(const std::wstring& text) {
	this->text = text;

	reset();
	sprites.reserve(text.size());

	if (text.empty())
		return;

	lines = getLines();
	calcMaxWidth();
	calcHeight();

	std::vector<float> alignOffsets = getAlignmentOffsets();
	int currentLine = 0;
	float x = alignOffsets[currentLine];
	float y = 0;

	int maxBaselineOffset = 0;

	for (int i = 0; i < text.size(); ++i) {
		if (text[i] == L'\n') {
			if (i != text.size() - 1) {
				x = alignOffsets[++currentLine];
				y -= GLYPH_SIZE_PX + maxBaselineOffset + LINE_SPACING;
				maxBaselineOffset = 0;
			}

			continue;
		}

		const FTCharacter& ftChar = FTLoader::getCharacter(text[i]);
		maxBaselineOffset = glm::max(maxBaselineOffset, ftChar.size.y - ftChar.bearing.y);

		x += ftChar.size.x * 0.5f + ftChar.bearing.x;

		sprites.push_back(std::move(createSprite(ftChar, x, y)));

		x += (ftChar.advance.x >> 6) - ftChar.size.x * 0.5f - ftChar.bearing.x;
	}
}

void Text2D::calcMaxWidth() {
	float maxWidth = 0;

	for (const std::wstring& line : lines) {
		maxWidth = glm::max(maxWidth, getWidth(line));
	}

	this->maxWidth = maxWidth * transform.scale.x;
}

void Text2D::calcHeight() {
	float height = 0;

	for (const std::wstring& line : lines) {
		height += getHeight(line);

		if (line != lines.back()) {
			height += LINE_SPACING;
		}
	}

	this->height = height * transform.scale.y;
}

std::vector<float> Text2D::getAlignmentOffsets() {
	std::vector<float> offsets;

	for (const std::wstring& line : lines) {
		offsets.push_back(getAlignmentOffset(line));
	}

	return offsets;
}

std::vector<std::wstring> Text2D::getLines() {
	std::vector<std::wstring> lines;
	std::wstring line;

	for (int i = 0; i < text.size(); ++i) {
		if (i == text.size() - 1 || text[i] == L'\n') {
			if (i == text.size() - 1)
				line.push_back(text[i]);

			lines.push_back(line);
			line.clear();
		}
		else {
			line.push_back(text[i]);
		}
	}

	return lines;
}

float Text2D::getAlignmentOffset(const std::wstring& line) {
	int lastIndex = 0;

	if (alignment == TextAlignment::CENTER)
		lastIndex = line.size() * 0.5f;
	else if (alignment == TextAlignment::RIGHT)
		lastIndex = line.size();

	float offset = -getWidth(line, lastIndex);

	if (alignment == TextAlignment::CENTER && line.size() % 2) {
		const FTCharacter& ftChar = FTLoader::getCharacter(line[lastIndex]);

		offset -= ftChar.advance.x >> 7;
	}

	return offset;
}

float Text2D::getWidth(const std::wstring& line, int length) {
	length = length == INT_MAX ? line.size() : length;
	float width = 0;

	for (int i = 0; i < length; ++i) {
		const FTCharacter& ftChar = FTLoader::getCharacter(line[i]);

		width += ftChar.advance.x >> 6;
	}

	return width;
}

int Text2D::getHeight(const std::wstring& line, int length) {
	length = length == INT_MAX ? line.size() : length;
	int maxHeight = 0;

	if (line.empty())
		return GLYPH_SIZE_PX;

	for (int i = 0; i < length; ++i) {
		const FTCharacter& ftChar = FTLoader::getCharacter(line[i]);

		maxHeight = glm::max(maxHeight, ftChar.size.y);
	}

	return maxHeight;
}

std::unique_ptr<Sprite> Text2D::createSprite(const FTCharacter& ftChar, float x, float y) {
	std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
	sprite->texture.data = ftChar.texture;
	sprite->texture.useAtlas = false;

	sprite->color = color;
	sprite->transform = transform;
	sprite->transform.rotation += glm::vec3(0, 180, 180);
	sprite->transform.position += transform.scale * glm::vec3(
		x,
		y + ftChar.bearing.y - ftChar.size.y * 0.5f - GLYPH_SIZE_PX * 0.5f,
		0
	);

	sprite->setup();

	return std::move(sprite);
}

void Text2D::draw(Shader& activeShader) {
	for (auto& sprite : sprites) {
		sprite->draw(activeShader);
	}
}

void Text2D::reset() {
	sprites.clear();
}

void Text2D::setColor(const glm::vec4& color) {
	for (auto& sprite : sprites) {
		sprite->color = color;
	}
}

void Text2D::setPosition(const glm::vec3& position) {
	for (auto& sprite : sprites) {
		sprite->transform.position += position - transform.position;
	}

	transform.position = position;
}

void Text2D::setScale(const glm::vec3& scale) {
	transform.scale = scale;

	setText(text);
}