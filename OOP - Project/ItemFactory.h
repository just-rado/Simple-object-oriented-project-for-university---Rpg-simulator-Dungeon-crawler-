#pragma once
#include "Item.h"

class ItemFactory
{
public:
	static Item* loadItemFromFile(std::ifstream& is, TypeOfItem type ,uint64_t ID);
};

