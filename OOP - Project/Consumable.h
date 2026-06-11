#pragma once
#include "Item.h"
#include "StatusEffects.h"
class Consumable: public Item
{
public:
	Consumable(const ItemData& data, int hp_modifier, int mp_modifier, StatusEffect removeStatusEffect);

	Consumable& operator=(const Consumable& other) = delete;

	virtual Item* clone()const override;

	int getHPModifier()const;
	int getMPModifier()const;
	StatusEffect getStatusEffectToRemove()const;

private:
	int HP_Modifier;
	int MP_Modifier;
	StatusEffect removeStatusEffect;


	static constexpr TypeOfItem itemType = TypeOfItem::CONSUMABLE;

};

