#pragma once
#include "Spell.h"
#include "StatusEffects.h"
class CleanseSpell: public Spell
{
public:

	CleanseSpell(EffectOfSpell effect, StatusEffect statusEffect);

	virtual Spell* clone()const override;

	StatusEffect getStatusEffect()const;


private:
	StatusEffect removeStatusEffect;


	static constexpr TypeOfSpell type = TypeOfSpell::CLEANSE;
};

