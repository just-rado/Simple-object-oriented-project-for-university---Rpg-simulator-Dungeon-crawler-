#include "Armor.h"

Armor::Armor(const ItemData& data , unsigned int protectionValue, const CharacterStats& modifiers):
		Item(data), protectionValue(protectionValue) , modifiers(modifiers)
{
	setTypeOfItem(itemType);
}

Item* Armor::clone()const
{
	return new Armor(*this);
}



unsigned int Armor::getProtectionValue()const
{
	return this->protectionValue;
}
const CharacterStats& Armor::getModifiers()const
{
	return this->modifiers;
}