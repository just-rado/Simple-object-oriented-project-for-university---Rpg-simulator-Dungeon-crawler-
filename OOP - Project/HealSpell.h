#pragma once
#include "Spell.h"

class HealSpell: public Spell
{
public:

	HealSpell(const std::string& name, const std::string& description , AgmentationType damageType, unsigned int manaCost , unsigned int healValue);


	virtual Spell* clone()const override;
	unsigned int getHealValue()const;



private:
	unsigned int healValue;

	static constexpr TypeOfSpell TYPE = TypeOfSpell::HEAL;

};

