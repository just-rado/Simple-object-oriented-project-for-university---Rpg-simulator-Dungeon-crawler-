#pragma once
#include "Spell.h"
#include "DamageTypeAndEffects.h"
class CleanseSpell: public Spell
{
public:

	CleanseSpell(const std::string& name, const std::string& description , DamageType damageType, StatusEffectType statusEffect);

	virtual Spell* clone()const override;

	StatusEffectType getStatusEffect()const;


private:
	StatusEffectType removeStatusEffect;


	static constexpr TypeOfSpell type = TypeOfSpell::CLEANSE;
};

