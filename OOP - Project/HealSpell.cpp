#include "HealSpell.h"

HealSpell::HealSpell(const std::string& name, const std::string& description ,AugmentationType damageType,unsigned int manaCost , 
	unsigned int levelRequired ,unsigned int healValue):
	Spell(name, description , TYPE , damageType , manaCost , levelRequired) , healValue(healValue)
{
	
}


Spell* HealSpell::clone()const
{
	return new (std::nothrow)HealSpell(*this);
}
unsigned int HealSpell::getHealValue()const
{
	return this->healValue;
}

bool HealSpell::applyEffectOfSpell(Character* character)const
{
	if (!character)
	{
		return false;
	}
	character->setHP(character->getHP() + this->healValue);
	return true;
}