#include "HealSpell.h"

HealSpell::HealSpell(DamageType damageType, unsigned int healValue): Spell(type , damageType) , healValue(healValue)
{}


Spell* HealSpell::clone()const
{
	return new HealSpell(*this);
}
unsigned int HealSpell::getHealValue()const
{
	return this->healValue;
}