#pragma once
#include "Spell.h"
#include "DamageTypeAndEffects.h"
class CleanseSpell: public Spell
{
public:

	CleanseSpell(DamageType damageType, StatusEffectType statusEffect);

	virtual Spell* clone()const override;

	StatusEffectType getStatusEffect()const;


private:
	StatusEffectType removeStatusEffect;


	static constexpr TypeOfSpell type = TypeOfSpell::CLEANSE;
};

