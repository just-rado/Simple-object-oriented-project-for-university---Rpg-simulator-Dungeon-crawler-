#pragma once
#include "item.h"
#include "DamageTypeAndEffects.h"
class Weapon: public Item
{
public:
	Weapon(const ItemData& data, DamageType type , unsigned int dmgValue , float criticalChance);

	Weapon& operator=(const Weapon& other) = delete;

	DamageType getType()const;
	unsigned int getDmgValue()const;
	float getCriticalChance()const;

	virtual Item* clone()const override;

private:
	DamageType type;
	unsigned int dmgValue;
	float criticalChance;

	static constexpr TypeOfItem itemType = TypeOfItem::WEAPON;
	static constexpr float MIN_CRITICAL_CHANCE = 0;
	static constexpr float MAX_CRITICAL_CHANCE = 100;
};

