#pragma once
#include "Item.h"
#include "CharacterStats.h"

class Armor: public Item
{
public:

	Armor(const ItemData& data , unsigned int protectionValue , const CharacterStats& modifiers);

	Armor(std::ifstream& read, uint64_t ID);
	virtual void writeDataToFile(std::ofstream& write)const override;

	Armor& operator=(const Armor& other) = delete;

	virtual Item* clone()const override;
	virtual void applyEffectsOfItem(Character* character)const override;
	virtual void removeEffectsOfItem(Character* character)const override;
	unsigned int getProtectionValue()const;
	const CharacterStats& getModifiers()const;

private:
	unsigned int protectionValue;
	CharacterStats modifiers;

	static constexpr TypeOfItem ITEM_TYPE = TypeOfItem::ARMOR;
	
};

