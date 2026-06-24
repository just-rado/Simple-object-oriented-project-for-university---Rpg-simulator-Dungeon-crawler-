#include "Armor.h"

Armor::Armor(const ItemData& data , unsigned int protectionValue, const CharacterStats& modifiers):
		Item(data , ITEM_TYPE), protectionValue(protectionValue) , modifiers(modifiers)
{
	
}

Armor::Armor(std::ifstream& read, uint64_t ID) : Item(read , ITEM_TYPE , ID)
{
	read.read(reinterpret_cast<char*>(&this->protectionValue), sizeof(this->protectionValue));

	read.read(reinterpret_cast<char*>(&this->modifiers), sizeof(this->modifiers));
	

	if (!read)
	{
		throw std::runtime_error("Could not read armor");
	}

}
void Armor::writeDataToFile(std::ofstream& write)const
{
	Item::writeDataToFile(write);

	write.write(reinterpret_cast<const char*>(&this->protectionValue), sizeof(this->protectionValue));

	write.write(reinterpret_cast<const char*>(&this->modifiers), sizeof(this->modifiers));

	if (!write)
	{
		throw std::runtime_error("Could not write armor");
	}

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