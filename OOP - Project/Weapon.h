#pragma once
#include "item.h"
#include "DamageTypeAndEffects.h"
class Weapon: public Item
{
public:
	Weapon(const ItemData& data, AugmentationType type , unsigned int dmgValue , unsigned int criticalChance);

	Weapon& operator=(const Weapon& other) = delete;

	unsigned int getDmgValue()const;
	unsigned int getCriticalChance()const;

	virtual AugmentationType getAugmentationType()const override;
	virtual Item* clone()const override;

private:
	AugmentationType type;
	unsigned int dmgValue;
	unsigned int criticalChance;

	static constexpr TypeOfItem ITEM_TYPE = TypeOfItem::WEAPON;
	static constexpr int MIN_CRITICAL_CHANCE = 0;
	static constexpr int MAX_CRITICAL_CHANCE = 100;
};

