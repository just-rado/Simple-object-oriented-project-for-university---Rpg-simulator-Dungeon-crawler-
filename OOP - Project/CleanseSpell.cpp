#include "CleanseSpell.h"

CleanseSpell::CleanseSpell(EffectOfSpell effect ,StatusEffect statusEffect) :Spell(type, effect), removeStatusEffect(statusEffect)
{}

Spell* CleanseSpell::clone()const
{
	return new CleanseSpell(*this);
}

StatusEffect CleanseSpell::getStatusEffect()const
{
	return this->removeStatusEffect;
}