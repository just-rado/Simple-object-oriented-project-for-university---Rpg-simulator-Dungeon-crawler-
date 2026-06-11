#pragma once
#include "Spell.h"
class DamageSpell: public Spell
{
public:

	DamageSpell(DamageType damageType, unsigned int dmgValue);


	virtual Spell* clone()const override;
	unsigned int getDamageValue()const;

private:

	unsigned int damageValue;

	static constexpr TypeOfSpell type = TypeOfSpell::DAMAGE;
};

