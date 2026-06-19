#include "HealSpell.h"

HealSpell::HealSpell(const std::string& name, const std::string& description ,AgmentationType damageType,unsigned int manaCost , unsigned int healValue): 
	Spell(name, description , TYPE , damageType , manaCost) , healValue(healValue)
{
	
}


Spell* HealSpell::clone()const
{
	return new HealSpell(*this);
}
unsigned int HealSpell::getHealValue()const
{
	return this->healValue;
}