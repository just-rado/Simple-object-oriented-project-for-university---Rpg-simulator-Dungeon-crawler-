#include "CleanseSpell.h"

CleanseSpell::CleanseSpell(const std::string& name, const std::string& description ,DamageType damageType,StatusEffectType statusEffect):
	Spell( name,description ,type, damageType), removeStatusEffect(statusEffect)
{}

Spell* CleanseSpell::clone()const
{
	return new CleanseSpell(*this);
}

StatusEffectType CleanseSpell::getStatusEffect()const
{
	return this->removeStatusEffect;
}