#pragma once
#include "DamageTypeAndEffects.h"

enum class TypeOfSpell
{
	DAMAGE,
	HEAL,
	CLEANSE,
};



class Spell
{
public:

	Spell(TypeOfSpell type, DamageType damageType);

	virtual ~Spell() = default;

	virtual Spell* clone()const = 0;

	TypeOfSpell getEffect()const;
	DamageType getType()const;

private:
	TypeOfSpell type;
	DamageType damageType;
	


};

