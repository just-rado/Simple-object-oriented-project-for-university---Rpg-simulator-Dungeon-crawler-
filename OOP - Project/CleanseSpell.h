#pragma once
#include "Spell.h"
#include "DamageTypeAndEffects.h"
class CleanseSpell: public Spell
{
public:

	CleanseSpell(const std::string& name, const std::string& description , AugmentationType damageType, unsigned int manaCost, 
		unsigned int levelRequired , StatusEffectType statusEffect);

	CleanseSpell(std::ifstream& read);

	virtual void writeDataToFile(std::ofstream& write)const override;


	virtual Spell* clone()const override;
	virtual bool applyEffectOfSpell(Character* character)const override;

	StatusEffectType getStatusEffect()const;


private:
	StatusEffectType removeStatusEffect;


	static constexpr TypeOfSpell TYPE = TypeOfSpell::CLEANSE;
};

