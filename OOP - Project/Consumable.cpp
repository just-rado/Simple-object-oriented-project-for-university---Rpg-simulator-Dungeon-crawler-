#include "Consumable.h"

Consumable::Consumable(const ItemData& data, int hp_modifier, int mp_modifier, int removeStatusEffect) :
	Item(data), HP_Modifier(hp_modifier), MP_Modifier(mp_modifier), removeStatusEffect(removeStatusEffect)
{
	// maybe add logic for status effect
}

Item* Consumable::clone()const
{
	return new Consumable(*this);
}

int Consumable::getHPModifier()const
{
	return this->HP_Modifier;
}
int Consumable::getMPModifier()const
{
	return this->MP_Modifier;
}
int Consumable::getStatusEffectToRemove()const
{
	return this->removeStatusEffect;
}