#include "ItemMeta.h"

ItemMeta::ItemMeta(const std::wstring& name, const std::vector<std::wstring>& lore)
	: name(name), lore(lore) {
	updateDescription();
}

void ItemMeta::setName(const std::wstring& name) {
	this->name = name;

	updateDescription();
}

void ItemMeta::setLore(const std::vector<std::wstring>& lore) {
	this->lore = lore;

	updateDescription();
}

void ItemMeta::updateDescription() {
	description = name;

	if (!lore.empty()) {
		description += L"\n\n";

		for (const std::wstring& line : lore)
			description += L" " + line + L"\n";
	}
}