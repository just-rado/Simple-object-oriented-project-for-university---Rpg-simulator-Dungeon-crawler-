#pragma once
#include <string>
#include "DamageTypeAndEffects.h"
#include "Character.h"

enum class TypeOfSpell
{
	DAMAGE,
	HEAL,
	CLEANSE,
};



class Spell
{
public:

	Spell(const std::string& name , const std::string& description , TypeOfSpell type, AugmentationType damageType , 
		unsigned int manaCost , unsigned int levelRequired);

	virtual ~Spell() = default;

	virtual Spell* clone()const = 0;

	virtual bool applyEffectOfSpell(Character* character)const = 0;

	TypeOfSpell getEffect()const;
	AugmentationType getType()const;
	unsigned int getManaCost()const;
	unsigned int getLevelRequired()const;
	const std::string& getName()const;
	const std::string& getDescription()const;

private:
	const std::string name;
	std::string description;
	TypeOfSpell type;
	AugmentationType damageType;
	unsigned int manaCost;
	unsigned int levelRequired;


};

