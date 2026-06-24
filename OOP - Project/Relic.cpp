#include "Relic.h"



Relic::Relic(const ItemData& data , const CharacterStats& modifiers): Item(data , ITEM_TYPE) , modifiers(modifiers)
{}


Relic::Relic(std::ifstream& read, uint64_t ID): Item(read , ITEM_TYPE , ID)
{
	read.read(reinterpret_cast<char*>(&this->modifiers), sizeof(this->modifiers));

	if (!read)
	{
		throw std::runtime_error("Could not load relic data");
	}
}
void Relic::writeDataToFile(std::ofstream& write)const
{
	write.write(reinterpret_cast<const char*>(&this->modifiers), sizeof(this->modifiers));

	if (!write)
	{
		throw std::runtime_error("Could not save relic data");
	}
}


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