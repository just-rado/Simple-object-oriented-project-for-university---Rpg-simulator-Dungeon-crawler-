#include "Armor.h"

Armor::Armor(const ItemData& data , unsigned int protectionValue, const CharacterStats& modifiers):
		Item(data , ITEM_TYPE), protectionValue(protectionValue) , modifiers(modifiers)
{
	
}

Item* Armor::clone()const
{
	return new Armor(*this);
}

void Armor::applyEffectsOfItem(Character* character)const
{
	if (!character)
	{
		return;
	}
	character->addCharacterStatsModifiers(this->getModifiers());
}
void Armor::removeEffectsOfItem(Character* character)const
{
	if (!character)
	{
		return;
	}
	character->removeCharacterStatsModifiers(this->getModifiers());
}


unsigned int Armor::getProtectionValue()const
{
	return this->protectionValue;
}
const CharacterStats& Armor::getModifiers()const
{
	return this->modifiers;
}