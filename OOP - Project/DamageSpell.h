#pragma once
#include "Spell.h"
class DamageSpell: public Spell
{
public:

	DamageSpell(const std::string& name, const std::string& description , AgmentationType damageType, unsigned int manaCost , unsigned int dmgValue);


	virtual Spell* clone()const override;
	unsigned int getDamageValue()const;

private:

	unsigned int damageValue;

	static constexpr TypeOfSpell TYPE = TypeOfSpell::DAMAGE;
};

