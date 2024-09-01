#include "InventoryGUI.h"

#include "../window/Window.h"
#include "GUIManager.h"
#include "GUI.h"

constexpr float
PADDING_WIDTH = 28.0f,
PADDING_BOTTOM = 18.0f,
PADDING_TOP = 58.0f,
PADDING_BETWEEN_TOPCENTER = 52.0f,
PADDING_BETWEEN_CENTERBOTTOM = 20.0f,

INVENTORY_PADDING_WIDTH = 2 * PADDING_WIDTH,
INVENTORY_PADDING_HEIGHT = PADDING_BOTTOM + PADDING_BETWEEN_CENTERBOTTOM + PADDING_BETWEEN_TOPCENTER + PADDING_TOP,

ITEM_DESCRIPTION_MIN_WIDTH = 250.0f,
ITEM_DESCRIPTION_PADDING_WIDTH = 10.0f,
ITEM_DESCRIPTION_PADDING_TOP = 30.0f,
ITEM_DESCRIPTION_PADDING_BOTTOM = 5.0f,

DEFAULT_BACKGROUND_WIDTH = 248,
DEFAULT_BACKGROUND_HEIGHT = 166;

constexpr glm::vec3
TITLE_OFFSET = glm::vec3(0.0f, 40.0f, 0),
TITLE_SCALE = glm::vec3(0.25f),
ITEM_DESCIPTION_OFFSET = glm::vec3(30, 30, 0),
ITEM_DESCRIPTION_TEXT_SCALE = glm::vec3(0.15f);

constexpr glm::vec4 TITLE_COLOR = glm::vec4(glm::vec3(0.3f), 1.0f);

std::shared_ptr<GUIElement> InventoryGUI::item_description;

void InventoryGUI::update(Player& player, bool& windowScaled) {
	GUIElement* inventory = GUIDatabase::root["inventory"].get();
	item_description = GUIDatabase::root["item_description"];
	item_description->visible = inventory->visible = player.isOpenedBackpack();

	InventoryView& hotbarView = player.getHotbarView();

	if (windowScaled || hotbarView.isNeedUpdate()) {
		updateHotbar(player);

		hotbarView.setNeedUpdate(false);
	}

	if (!inventory->visible)
		return;

	updateItemDesciption(player);
	updateDraggedItem(player);

	if (!windowScaled && !player.isNeedUpdateInventoryViews())
		return;

	updateOpenInventory(player);

	player.setNeedUpdateInventoryViews(false);
}

void InventoryGUI::updateItemDesciption(Player& player) {
	InventoryItem invItem = GUIManager::getItemOnCursor(player);

	if (!invItem.isValid() || !invItem.item->hasMeta()) {
		item_description->visible = false;

		return;
	}

	item_description->layer_offset = GUI_ELEMENT_MAX_LAYER - 1;
	item_description->visible = true;

	std::shared_ptr<GUIElement> textElement = item_description->children["text"];

	textElement->text->setScale(ITEM_DESCRIPTION_TEXT_SCALE);
	textElement->text->setText(invItem.item->getMeta().getDescription());

	float textWidth = textElement->text->getMaxWidth();
	float textHeight = textElement->text->getHeight();
	
	float width = glm::max(ITEM_DESCRIPTION_MIN_WIDTH, textWidth + 2 * ITEM_DESCRIPTION_PADDING_WIDTH);
	float height = textHeight + ITEM_DESCRIPTION_PADDING_TOP + ITEM_DESCRIPTION_PADDING_BOTTOM;

	item_description->transform.position = glm::vec3(
		invItem.element->transform.position.x + ITEM_DESCIPTION_OFFSET.x + width * 0.5f,
		invItem.element->transform.position.y + ITEM_DESCIPTION_OFFSET.y - height * 0.5f,
		0
	);

	item_description->transform.scale = GUIManager::scale(
		glm::vec3(1),
		DEFAULT_BACKGROUND_WIDTH,
		DEFAULT_BACKGROUND_HEIGHT,
		width,
		height
	);

	textElement->text->setPosition(glm::vec3(
		item_description->transform.position.x - 0.5f * width + ITEM_DESCRIPTION_PADDING_WIDTH,
		item_description->transform.position.y + 0.5f * height - ITEM_DESCRIPTION_PADDING_TOP,
		0
	));

	item_description->children.emplace(textElement->name, textElement);

	GUI::setupElement(*item_description);
}

void InventoryGUI::updateDraggedItem(Player& player) {
	const InventoryItem& invItem = player.getDraggedItem();

	if (!invItem.isValid())
		return;

	glm::vec3 position = glm::vec3(Window::getCursorPosRelativeToCenter(), 0);
	position = GUIManager::scale(position, Window::getWidth(), Window::getHeight(), GUI_DEFAULT_WIDTH, GUI_DEFAULT_HEIGHT);

	invItem.element->transform.position = position;
	invItem.element->layer_offset = GUI_ELEMENT_MAX_LAYER - 1;
	invItem.element->children["amount"]->visible = false;

	GUI::setupElement(*invItem.element);
}

void InventoryGUI::updateHotbar(Player& player) {
	std::shared_ptr<GUIElement> hotbar = GUIDatabase::root["hotbar"];
	hotbar->children.clear();

	const InventoryView& hotbarView = player.getHotbarView();
	hotbar->children = hotbarView.getGUISector(hotbar);

	std::shared_ptr<GUIElement> hotbarViewElement = hotbar->children["0"];
	std::shared_ptr<GUIElement> frame = std::make_shared<GUIElement>(*GUIDatabase::root["slot_frame"]);

	frame->parent = std::shared_ptr<GUIElement>(hotbarViewElement);
	frame->transform.scale = frame->parent->transform.scale;
	frame->transform.position.x = DEFAULT_SLOT_WIDTH * frame->transform.scale.x * (player.getSelectedSlot() - 0.5f * (SLOTS_IN_ROW - 1));
	frame->transform.position += frame->parent->transform.position;
	frame->visible = true;

	hotbarViewElement->children.emplace("frame", frame);

	GUI::setupElement(*hotbar);
}

void InventoryGUI::updateOpenInventory(Player& player) {
	GUIElement* inventory = GUIDatabase::root["inventory"].get();
	GUIElement* background = inventory->children["background"].get();

	const InventoryView* top = player.getOpenInventoryView();
	const InventoryView& center = player.getBackpackView();
	const InventoryView& bottom = player.getHotbarView();

	int topRowsNumber = top != nullptr ? top->getRowsNumber() : 0;
	glm::vec2 slotSize = InventoryView::getSlotSize();

	float width = INVENTORY_PADDING_WIDTH + slotSize.x * SLOTS_IN_ROW;
	float height = INVENTORY_PADDING_HEIGHT + slotSize.y * (bottom.getRowsNumber() + center.getRowsNumber() + topRowsNumber)
		+ (top == nullptr ? -PADDING_BETWEEN_TOPCENTER : 0.0f);

	background->transform.scale = GUIManager::scale(
		glm::vec3(1),
		DEFAULT_BACKGROUND_WIDTH,
		DEFAULT_BACKGROUND_HEIGHT,
		width,
		height
	);

	std::shared_ptr<GUIElement> bottomElement = background->children["bottom"];
	bottomElement->transform.position
		= glm::vec3(bottom.getSectorCenter() + glm::vec2(PADDING_WIDTH, PADDING_BOTTOM), 0);

	std::shared_ptr<GUIElement> centerElement = background->children["center"];
	centerElement->transform.position =
		bottomElement->transform.position
		+ glm::vec3(0, bottom.getSectorCenter().y + PADDING_BETWEEN_CENTERBOTTOM + center.getSectorCenter().y - 0.5f * slotSize.y, 0);

	std::shared_ptr<GUIElement> topElement = background->children["top"];

	if (top != nullptr) {
		topElement->transform.position
			= centerElement->transform.position
			+ glm::vec3(0, center.getSectorCenter().y + PADDING_BETWEEN_TOPCENTER + top->getSectorCenter().y + 0.5f * slotSize.y, 0);
	}

	glm::vec3 bottomLeft = -0.5f * glm::vec3(width, height, 0);

	updateInventoryElement(bottomElement, bottom, bottomLeft);
	updateInventoryElement(centerElement, center, bottomLeft);
	updateInventoryViewTitle(centerElement, center, TextAlignment::LEFT);

	if (top != nullptr) {
		updateInventoryElement(topElement, *top, bottomLeft);
		topElement->transform.position.y -= 0.5f * slotSize.y;

		updateInventoryViewTitle(topElement, *top, TextAlignment::CENTER);
	} else {
		topElement->children.clear();
	}

	GUI::setupElement(*background);
}

void InventoryGUI::updateInventoryElement(std::shared_ptr<GUIElement>& element, const InventoryView& view, const glm::vec3& bottomLeft) {
	element->children.clear();

	element->transform.position += bottomLeft;
	element->children = view.getGUISector(element);
}

void InventoryGUI::updateInventoryViewTitle(std::shared_ptr<GUIElement>& element, const InventoryView& view, TextAlignment titleAlignment) {
	float dx = 0;

	if (titleAlignment == TextAlignment::LEFT)
		dx = -view.getSectorCenter().x;
	else if (titleAlignment == TextAlignment::RIGHT)
		dx = view.getSectorCenter().x;

	Transform transform = Transform(
		glm::vec3(
			TITLE_OFFSET.x + dx, 
			TITLE_OFFSET.y + view.getSectorCenter().y, 
			0
		) + element->transform.position,
		glm::vec3(0),
		glm::vec3(TITLE_SCALE)
	);

	std::shared_ptr<Text2D> titleText = std::make_shared<Text2D>(
		view.getInventory().getTitle(),
		titleAlignment,
		transform,
		TITLE_COLOR
	);

	std::shared_ptr<GUIElement> titleElement = std::make_shared<GUIElement>(
		"title",
		titleText,
		true,
		element
	);

	element->children.emplace(titleElement->name, titleElement);
}