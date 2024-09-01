#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include "../GL/GLHelper.h"

#include "../render/model/Model.h"
#include "ItemStack.h"

class ItemModel : public Model {
	const std::shared_ptr<ItemStack> item;
	std::unique_ptr<MeshData> meshData;
	bool blockItem = false;
	float size;

	void bindTexture(Shader& shader);

	void setupItem();
	void setupBlockItem();
	void addIndices(int& vertIndex);
	void addBlockFace(const std::array<float, 12>& vertices, const glm::vec2& textureCoords, int& vertIndex);
	void addItemPixel(int x, int y, int& vertIndex, int texSize, const std::vector<std::vector<glm::vec4>>& colors);
	void addItemPixelFace(
		const glm::vec4& color,
		int& vertIndex, const int& texSize,
		const int& px, const int& py,
		int&& x_lb, int&& y_lb, int&& z_lb,
		int&& x_rb, int&& y_rb, int&& z_rb,
		int&& x_rt, int&& y_rt, int&& z_rt,
		int&& x_lt, int&& y_lt, int&& z_lt
	);

	void reset() override {}
public:
	ItemModel(const std::shared_ptr<ItemStack>& item, float size);

	bool isBlockItem() { return blockItem; }
};

#endif