#include "DamageSpell.h"

DamageSpell::DamageSpell(DamageType damageType , unsigned int dmgValue):Spell(type , damageType) , damageValue(dmgValue)
{}


Spell* DamageSpell::clone()const
{
	return new DamageSpell(*this);
 }
unsigned int DamageSpell::getDamageValue()const
{
	return this->damageValue;
}