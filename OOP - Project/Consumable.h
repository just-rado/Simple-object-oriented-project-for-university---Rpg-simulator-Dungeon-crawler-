#pragma once
#include "Item.h"
#include "DamageTypeAndEffects.h"
class Consumable: public Item
{
public:
	Consumable(const ItemData& data, int hp_modifier, int mp_modifier, StatusEffectType removeStatusEffect);

	Consumable& operator=(const Consumable& other) = delete;

	virtual Item* clone()const override;

	int getHPModifier()const;
	int getMPModifier()const;
	StatusEffectType getStatusEffectToRemove()const;

private:
	int HP_Modifier;
	int MP_Modifier;
	StatusEffectType removeStatusEffect;


	static constexpr TypeOfItem itemType = TypeOfItem::CONSUMABLE;

};

