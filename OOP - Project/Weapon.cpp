#include "Weapon.h"
#include <stdexcept>

Weapon::Weapon(const ItemData& data, DamageType type, unsigned int dmgValue, float criticalChance) : 
	Item(data), type(type) , dmgValue(dmgValue) , criticalChance(criticalChance)
{
	if (criticalChance < MIN_CRITICAL_CHANCE || criticalChance > MAX_CRITICAL_CHANCE)
	{
		throw std::invalid_argument("Invalid critical chance");
	}

	setTypeOfItem(itemType);
}

Item* Weapon::clone()const
{
	return new Weapon(*this);
}


DamageType Weapon::getType()const
{
	return this->type;
}
unsigned int Weapon::getDmgValue()const
{
	return this->dmgValue;
}
float Weapon::getCriticalChance()const
{
	return this->criticalChance;
}