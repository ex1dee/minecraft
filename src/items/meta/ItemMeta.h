#ifndef ITEMMETA_H
#define ITEMMETA_H

#include <vector>
#include <string>

class ItemMeta {
	std::wstring name;
	std::vector<std::wstring> lore;
	std::wstring description;
	
	void updateDescription();
public:
	ItemMeta() = default;
	ItemMeta(const std::wstring& name, const std::vector<std::wstring>& lore);

	const std::wstring& getName() const { return name; }
	const std::vector<std::wstring>& getLore() const { return lore; }
	const std::wstring& getDescription() const { return description; }

	void setName(const std::wstring& name);
	void setLore(const std::vector<std::wstring>& lore);
};

enum class ItemMetaID {
	DEFAULT = 0
};

#endif