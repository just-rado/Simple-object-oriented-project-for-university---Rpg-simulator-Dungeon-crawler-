#include "HealSpell.h"

HealSpell::HealSpell(EffectOfSpell effect, unsigned int healValue): Spell(type , effect) , healValue(healValue)
{}


Spell* HealSpell::clone()const
{
	return new HealSpell(*this);
}
unsigned int HealSpell::getHealValue()const
{
	return this->healValue;
}