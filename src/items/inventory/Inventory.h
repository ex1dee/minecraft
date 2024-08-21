#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

#include "../ItemStack.h"

constexpr int 
SLOTS_IN_ROW = 9,
MAX_ROWS_NUMBER = 6;

class InventoryView;

class Inventory {
	std::vector<std::shared_ptr<ItemStack>> items;
	std::vector<InventoryView*> views;
	std::wstring title;
	int rowsNumber;
	int size;

	inline int getIndex(int column, int row) const { return row * SLOTS_IN_ROW + column; }
	inline bool isCorrectIndex(int index) const { return index >= 0 && index < size; }
public:
	Inventory(const std::wstring& title, int rowsNumber);

	int getRowsNumber() const { return rowsNumber; }
	const std::wstring& getTitle() const { return title; }

	void updateViews();
	void hookView(InventoryView& view);
	std::shared_ptr<ItemStack> getItem(int index) const;
	std::shared_ptr<ItemStack> getItem(int column, int row) const;
	void setItem(int column, int row, const ItemStack& item);
	void setItem(int index, const ItemStack& item);
	void addItem(const ItemStack& item);
};

#endif