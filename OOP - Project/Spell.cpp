#include "Spell.h"

Spell::Spell(TypeOfSpell type, EffectOfSpell effect):type(type) , effect(effect)
{}

TypeOfSpell Spell::getEffect()const
{
	return this->type;
}
EffectOfSpell Spell::getType()const
{
	return this->effect;
}


