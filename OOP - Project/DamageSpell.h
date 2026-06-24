#pragma once
#include "Spell.h"
class DamageSpell: public Spell
{
public:

	DamageSpell(const std::string& name, const std::string& description , AugmentationType damageType, unsigned int manaCost,
		unsigned int levelRequired, int dmgValue);

	virtual bool applyEffectOfSpell(Character* character)const override;

	virtual Spell* clone()const override;
	 int getDamageValue()const;

private:

	int damageValue;

	static constexpr TypeOfSpell TYPE = TypeOfSpell::DAMAGE;
};

