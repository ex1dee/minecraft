#include "ItemModel.h"

#include "../world/block/BlockMeshConstants.h"

ItemModel::ItemModel(const std::shared_ptr<ItemStack>& item, float size)
	: item(item), size(size) {
	meshData = std::make_unique<MeshData>(MeshType::ITEM, 3);

	if (item->getType().hasCubeMesh()) {
		setupBlockItem();
	} else {
		setupItem();
	}

	addMesh(meshData);
}

void ItemModel::setupBlockItem() {
	const BlockType& blockType = BlocksDatabase::get(item->getType().material);

	meshData->textures.push_back(BlocksDatabase::getTextureAtlas());
	blockItem = true;

	int vertIndex = 0;

	addBlockFace(bottomFace, blockType.texBottomCoords, vertIndex);
	addBlockFace(topFace,	 blockType.texTopCoords,	vertIndex);
	addBlockFace(rightFace,  blockType.texSideCoords,	vertIndex);
	addBlockFace(leftFace,   blockType.texSideCoords,	vertIndex);
	addBlockFace(frontFace,  blockType.texSideCoords,	vertIndex);
	addBlockFace(backFace,   blockType.texSideCoords,	vertIndex);
}

void ItemModel::addBlockFace(const std::array<float, 12>& vertices, const glm::vec2& textureCoords, int& vertIndex) {
	for (float coord : vertices) {
		meshData->vertexPositions.push_back(coord * size);
	}

	AtlasCoords atlasCoords = BlocksDatabase::getTextureAtlas()->getTextureCoords(textureCoords);
	atlasCoords.addToTexCoords(meshData->textureCoords);

	addIndices(vertIndex);
}

void ItemModel::setupItem() {
	const std::shared_ptr<Texture>& texture = item->getType().texture.data;
	const unsigned char* const texData = texture->getData();
	const int texSize = texture->getWidth();

	assert(texture->getWidth() == texture->getHeight());

	std::vector<std::vector<glm::vec4>> colors(texSize, std::vector<glm::vec4>(texSize));

	for (int x = 0; x < texSize; ++x) {
		for (int y = 0; y < texSize; ++y) {
			colors[x][y] = texture->getColor(x, y);
		}
	}

	int vertIndex = 0;

	for (int x = 0; x < texSize; ++x) {
		for (int y = 0; y < texSize; ++y) {
			if (colors[x][y].a == 0.0f)
				continue;

			addItemPixel(x, y, vertIndex, texSize, colors);
		}
	}
}

void ItemModel::addItemPixel(int x, int y, int& vertIndex, int texSize, const std::vector<std::vector<glm::vec4>>& colors) {
	addItemPixelFace(colors[x][y], vertIndex, texSize, x, y,
		0, 0, 0,
		1, 0, 0,
		1, 1, 0,
		0, 1, 0
	);

	addItemPixelFace(colors[x][y], vertIndex, texSize, x, y,
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1
	);

	if (x > 0 && colors[x - 1][y].a == 0.0f) {
		addItemPixelFace(colors[x][y], vertIndex, texSize, x, y,
			0, 0, 0,
			0, 0, 1,
			0, 1, 1,
			0, 1, 0
		);
	}

	if (x < texSize - 1 && colors[x + 1][y].a == 0.0f) {
		addItemPixelFace(colors[x][y], vertIndex, texSize, x, y,
			1, 0, 0,
			1, 0, 1,
			1, 1, 1,
			1, 1, 0
		);
	}

	if (y > 0 && colors[x][y - 1].a == 0.0f) {
		addItemPixelFace(colors[x][y], vertIndex, texSize, x, y,
			0, 0, 0,
			1, 0, 0,
			1, 0, 1,
			0, 0, 1
		);
	}

	if (y < texSize - 1 && colors[x][y + 1].a == 0.0f) {
		addItemPixelFace(colors[x][y], vertIndex, texSize, x, y,
			0, 1, 0,
			1, 1, 0,
			1, 1, 1,
			0, 1, 1
		);
	}
}

void ItemModel::addItemPixelFace(
	const glm::vec4& color,
	int& vertIndex, const int& texSize,
	const int& px, const int& py,
	int&& x_lb, int&& y_lb, int&& z_lb,
	int&& x_rb, int&& y_rb, int&& z_rb,
	int&& x_rt, int&& y_rt, int&& z_rt,
	int&& x_lt, int&& y_lt, int&& z_lt
) {
	const float pixelSize = size / (float) texSize;

	meshData->vertexPositions.push_back(pixelSize * (px + x_lb));
	meshData->vertexPositions.push_back(pixelSize * (py + y_lb));
	meshData->vertexPositions.push_back(pixelSize * z_lb);

	meshData->vertexPositions.push_back(pixelSize * (px + x_rb));
	meshData->vertexPositions.push_back(pixelSize * (py + y_rb));
	meshData->vertexPositions.push_back(pixelSize * z_rb);

	meshData->vertexPositions.push_back(pixelSize * (px + x_rt));
	meshData->vertexPositions.push_back(pixelSize * (py + y_rt));
	meshData->vertexPositions.push_back(pixelSize * z_rt);

	meshData->vertexPositions.push_back(pixelSize * (px + x_lt));
	meshData->vertexPositions.push_back(pixelSize * (py + y_lt));
	meshData->vertexPositions.push_back(pixelSize * z_lt);

	addIndices(vertIndex);

	for (int i = 0; i < 4; ++i) {
		meshData->colors.push_back(color.r);
		meshData->colors.push_back(color.g);
		meshData->colors.push_back(color.b);
		meshData->colors.push_back(color.a);
	}
}

void ItemModel::addIndices(int& vertIndex) {
	meshData->indices.push_back(vertIndex);
	meshData->indices.push_back(vertIndex + 1);
	meshData->indices.push_back(vertIndex + 2);

	meshData->indices.push_back(vertIndex);
	meshData->indices.push_back(vertIndex + 2);
	meshData->indices.push_back(vertIndex + 3);

	vertIndex += 4;
}

void ItemModel::bindTexture(Shader& shader) {
	if (blockItem)
		TextureManager::bindTexture(*BlocksDatabase::getTextureAtlas(), shader, DEFAULT_TEXTURE_UNIFORM);
}