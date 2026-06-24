#include "Relic.h"



Relic::Relic(const ItemData& data , const CharacterStats& modifiers): Item(data , ITEM_TYPE) , modifiers(modifiers)
{}


CharacterStats Relic::getStats()const
{
	return this->modifiers;
}


void Relic::applyEffectsOfItem(Character* character)const
{
	if (!character)
	{
		return;
	}
	character->addCharacterStatsModifiers(this->modifiers);
}
void Relic::removeEffectsOfItem(Character* character)const
{
	if (!character)
	{
		return;
	}
	character->removeCharacterStatsModifiers(this->modifiers);
}

Item* Relic::clone()const
{
	return new Relic(*this);
}