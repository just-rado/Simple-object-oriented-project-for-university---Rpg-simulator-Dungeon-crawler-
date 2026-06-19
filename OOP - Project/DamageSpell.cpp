#include "DamageSpell.h"

DamageSpell::DamageSpell(const std::string& name, const std::string& description ,AgmentationType damageType ,unsigned int manaCost, unsigned int dmgValue):
	Spell(name , description , TYPE , damageType , manaCost) , damageValue(dmgValue)
{}


Spell* DamageSpell::clone()const
{
	return new DamageSpell(*this);
 }
unsigned int DamageSpell::getDamageValue()const
{
	return this->damageValue;
}