#include "Relic.h"



Relic::Relic(const ItemData& data , const CharacterStats& modifiers): Item(data) , modifiers(modifiers)
{}


Item* Relic::clone()const
{
	return new Relic(*this);
}