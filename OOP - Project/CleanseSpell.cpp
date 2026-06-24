#include "CleanseSpell.h"
#include <stdexcept>
CleanseSpell::CleanseSpell(const std::string& name, const std::string& description ,AugmentationType damageType,
	unsigned int manaCost , unsigned int levelRequired ,StatusEffectType statusEffect):
	Spell(name, description ,TYPE, damageType , manaCost , levelRequired), removeStatusEffect(statusEffect)
{
	if (statusEffect == StatusEffectType::NONE)
	{
		throw std::invalid_argument("Invalid");
	}
}

Spell* CleanseSpell::clone()const
{
	return new (std::nothrow)CleanseSpell(*this);
}

StatusEffectType CleanseSpell::getStatusEffect()const
{
	return this->removeStatusEffect;
}

bool CleanseSpell::applyEffectOfSpell(Character* character)const
{	
	if (!character)
	{
		return false;
	}
	character->removeStatusEffect(this->removeStatusEffect);
	return true;
}