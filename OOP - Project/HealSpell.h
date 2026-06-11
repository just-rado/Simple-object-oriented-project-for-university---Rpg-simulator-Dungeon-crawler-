#pragma once
#include "Spell.h"

class HealSpell: public Spell
{
public:

	HealSpell(DamageType damageType, unsigned int healValue);


	virtual Spell* clone()const override;
	unsigned int getHealValue()const;



private:
	unsigned int healValue;

	static constexpr TypeOfSpell type = TypeOfSpell::HEAL;

};

