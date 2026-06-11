#include "Spell.h"

Spell::Spell(TypeOfSpell type, DamageType damageType):type(type) , damageType(damageType)
{}

TypeOfSpell Spell::getEffect()const
{
	return this->type;
}
DamageType Spell::getType()const
{
	return this->damageType;
}


