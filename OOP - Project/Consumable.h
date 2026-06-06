#pragma once
#include "Item.h"
class Consumable: public Item
{
public:
	Consumable(const ItemData& data, int hp_modifier, int mp_modifier, int removeStatusEffect);// remake when status effect is not a int

	Consumable& operator=(const Consumable& other) = delete;

	virtual Item* clone()const override;

	int getHPModifier()const;
	int getMPModifier()const;
	int getStatusEffectToRemove()const;

private:
	int HP_Modifier;
	int MP_Modifier;
	int removeStatusEffect; // remake when you make a enum class for status effects (if status effects are a class)

};

