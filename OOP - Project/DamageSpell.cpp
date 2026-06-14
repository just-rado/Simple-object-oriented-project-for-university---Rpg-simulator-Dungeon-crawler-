#include "DamageSpell.h"

DamageSpell::DamageSpell(const std::string& name, const std::string& description ,DamageType damageType , unsigned int dmgValue):
	Spell(name , description , type , damageType) , damageValue(dmgValue)
{}


Spell* DamageSpell::clone()const
{
	return new DamageSpell(*this);
 }
unsigned int DamageSpell::getDamageValue()const
{
	return this->damageValue;
}