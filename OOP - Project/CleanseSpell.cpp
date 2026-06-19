#include "CleanseSpell.h"

CleanseSpell::CleanseSpell(const std::string& name, const std::string& description ,AgmentationType damageType,
	unsigned int manaCost ,StatusEffectType statusEffect):
	Spell(name,description ,TYPE, damageType , manaCost), removeStatusEffect(statusEffect)
{}

Spell* CleanseSpell::clone()const
{
	return new CleanseSpell(*this);
}

StatusEffectType CleanseSpell::getStatusEffect()const
{
	return this->removeStatusEffect;
}