#pragma once
#include <string>
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

	Spell(const std::string& name , const std::string& description , TypeOfSpell type, DamageType damageType);

	virtual ~Spell() = default;

	virtual Spell* clone()const = 0;

	TypeOfSpell getEffect()const;
	DamageType getType()const;
	const std::string& getName()const;
	const std::string& getDescription()const;

private:
	const std::string name;
	std::string description;

	DamageType damageType;
	
	TypeOfSpell type;

};

