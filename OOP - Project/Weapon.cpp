#include "Weapon.h"
#include <stdexcept>


Weapon::Weapon(const ItemData& data, AugmentationType type, unsigned int dmgValue, unsigned int criticalChance) : 
	Item(data , ITEM_TYPE), type(type) , dmgValue(dmgValue) , criticalChance(criticalChance)
{
	if (criticalChance < MIN_CRITICAL_CHANCE || criticalChance > MAX_CRITICAL_CHANCE)
	{
		throw std::invalid_argument("Invalid critical chance");
	}

	
}


Weapon::Weapon(std::ifstream& read, uint64_t ID): Item(read , ITEM_TYPE , ID)
{
	uint32_t augmentationTypeValue = 0;

	read.read(reinterpret_cast<char*>(&augmentationTypeValue), sizeof(augmentationTypeValue));

	this->type = static_cast<AugmentationType>(augmentationTypeValue);

	read.read(reinterpret_cast<char*>(&this->dmgValue), sizeof(this->dmgValue));

	read.read(reinterpret_cast<char*>(&this->criticalChance), sizeof(this->criticalChance));

	if (!read)
	{
		throw std::runtime_error("Error");
	}
}
void Weapon::writeDataToFile(std::ofstream& write)const
{
	Item::writeDataToFile(write);

	uint32_t augmentationTypeValue = static_cast<uint32_t>(this->type);

	write.write(reinterpret_cast<const char*>(&augmentationTypeValue), sizeof(augmentationTypeValue));

	write.write(reinterpret_cast<const char*>(&this->dmgValue), sizeof(this->dmgValue));

	write.write(reinterpret_cast<const char*>(&this->criticalChance), sizeof(this->criticalChance));

}


Item* Weapon::clone()const
{
	return new Weapon(*this);
}

AugmentationType Weapon::getAugmentationType()const
{
	return this->type;
}


unsigned int Weapon::getDmgValue()const
{
	return this->dmgValue;
}
unsigned int Weapon::getCriticalChance()const
{
	return this->criticalChance;
}