#include "Consumable.h"

Consumable::Consumable(const ItemData& data, int hp_modifier, int mp_modifier, StatusEffectType removeStatusEffect) :
	Item(data , ITEM_TYPE), HP_Modifier(hp_modifier), MP_Modifier(mp_modifier), removeStatusEffect(removeStatusEffect)
{
	
}

Item* Consumable::clone()const
{
	return new Consumable(*this);
}


void Consumable::applyEffectsOfItem(Character* character)const
{
	if (!character)
	{
		return;
	}
	character->setHP(character->getHP() + this->getHPModifier());
	character->setMP(character->getMP() + this->getMPModifier());
	character->removeStatusEffect(this->getStatusEffectToRemove());
}


int Consumable::getHPModifier()const
{
	return this->HP_Modifier;
}
int Consumable::getMPModifier()const
{
	return this->MP_Modifier;
}
StatusEffectType Consumable::getStatusEffectToRemove()const
{
	return this->removeStatusEffect;
}