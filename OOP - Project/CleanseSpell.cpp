#include "CleanseSpell.h"

CleanseSpell::CleanseSpell(DamageType damageType,StatusEffectType statusEffect) :Spell(type, damageType), removeStatusEffect(statusEffect)
{}

Spell* CleanseSpell::clone()const
{
	return new CleanseSpell(*this);
}

StatusEffectType CleanseSpell::getStatusEffect()const
{
	return this->removeStatusEffect;
}