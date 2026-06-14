#include "HealSpell.h"

HealSpell::HealSpell(const std::string& name, const std::string& description ,DamageType damageType, unsigned int healValue): 
	Spell(name, description , type , damageType) , healValue(healValue)
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