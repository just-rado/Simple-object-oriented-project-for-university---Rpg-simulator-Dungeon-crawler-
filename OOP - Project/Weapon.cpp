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