#pragma once
#include "item.h"
#include "DamageTypeAndEffects.h"
class Weapon: public Item
{
public:
	Weapon(const ItemData& data, AgmentationType type , unsigned int dmgValue , unsigned int criticalChance);

	Weapon& operator=(const Weapon& other) = delete;

	AgmentationType getDmgType()const;
	unsigned int getDmgValue()const;
	unsigned int getCriticalChance()const;

	virtual Item* clone()const override;

private:
	AgmentationType type;
	unsigned int dmgValue;
	unsigned int criticalChance;

	static constexpr TypeOfItem itemType = TypeOfItem::WEAPON;
	static constexpr int MIN_CRITICAL_CHANCE = 0;
	static constexpr int MAX_CRITICAL_CHANCE = 100;
};

