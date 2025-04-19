#include "Item.h"

Item::Item(const std::shared_ptr<ItemStack>& item)
	: item(item), Entity(ITEM) {
	std::shared_ptr<ItemModel> itemModel = std::make_shared<ItemModel>(item, getType().colliderExtents.x);
	setModel(std::dynamic_pointer_cast<Model>(itemModel));

	if (!itemModel->isBlockItem())
		transform.rotation.z = 90.0f;

	transform.rotateOrigin = getType().colliderExtents * 0.5f;
}