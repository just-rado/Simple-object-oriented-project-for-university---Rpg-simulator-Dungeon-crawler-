#pragma once
#include "Spell.h"
class DamageSpell: public Spell
{
public:

	DamageSpell(const std::string& name, const std::string& description , DamageType damageType, unsigned int dmgValue);


	virtual Spell* clone()const override;
	unsigned int getDamageValue()const;

private:

	unsigned int damageValue;

	static constexpr TypeOfSpell type = TypeOfSpell::DAMAGE;
};

