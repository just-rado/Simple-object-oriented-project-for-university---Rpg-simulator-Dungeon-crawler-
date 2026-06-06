#pragma once
#include "Item.h"
#include "CharacterStats.h"

class Armor: public Item
{
public:

	Armor(const ItemData& data , unsigned int protectionValue , const CharacterStats& modifiers);

	Armor& operator=(const Armor& other) = delete;

	virtual Item* clone()const override;

	unsigned int getProtectionValue()const;
	const CharacterStats& getModifiers()const;

private:
	unsigned int protectionValue;
	CharacterStats modifiers;
};

