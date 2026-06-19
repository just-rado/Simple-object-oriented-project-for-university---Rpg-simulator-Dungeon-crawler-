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

	Spell(const std::string& name , const std::string& description , TypeOfSpell type, AgmentationType damageType , unsigned int manaCost);

	virtual ~Spell() = default;

	virtual Spell* clone()const = 0;

	TypeOfSpell getEffect()const;
	AgmentationType getType()const;
	unsigned int getManaCost()const;
	const std::string& getName()const;
	const std::string& getDescription()const;

private:
	const std::string name;
	std::string description;
	TypeOfSpell type;
	AgmentationType damageType;
	unsigned int manaCost;


};

