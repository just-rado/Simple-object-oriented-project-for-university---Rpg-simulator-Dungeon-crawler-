#pragma once
#include "Spell.h"

class HealSpell: public Spell
{
public:

	HealSpell(const std::string& name, const std::string& description , AugmentationType damageType, unsigned int manaCost ,
		unsigned int levelRequired ,unsigned int healValue);


	virtual Spell* clone()const override;
	unsigned int getHealValue()const;

	virtual bool applyEffectOfSpell(Character* character)const override;


private:
	unsigned int healValue;

	static constexpr TypeOfSpell TYPE = TypeOfSpell::HEAL;

};

