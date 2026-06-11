#include "DamageSpell.h"

DamageSpell::DamageSpell(EffectOfSpell effect, unsigned int dmgValue):Spell(type , effect) , damageValue(dmgValue)
{}


Spell* DamageSpell::clone()const
{
	return new DamageSpell(*this);
 }
unsigned int DamageSpell::getDamageValue()const
{
	return this->damageValue;
}