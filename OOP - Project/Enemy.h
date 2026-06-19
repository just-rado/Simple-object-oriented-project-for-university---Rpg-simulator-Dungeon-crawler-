#pragma once
#include "Character.h"
#include "DamageTypeAndEffects.h"
#include "Hero.h"
#include <vector>

class Hero;
enum class TypeOfEnemy
{
	SKELETON,
	WEREWOLF,
};
class Enemy: public Character
{
public:
	Enemy(const CharacterData& mainStats, TypeOfEnemy type , const std::vector<AgmentationType> weakTo , unsigned int exp);
	
	TypeOfEnemy getType()const;

	const size_t getNumberOfWeaknesses()const;
	const AgmentationType getWeakTo(size_t index)const;
	
	unsigned int getExpGainedForKilling()const;

	virtual void attackHero(Hero* hero) = 0;
	virtual Enemy* clone()const = 0;
private:

	TypeOfEnemy type;
	std::vector<AgmentationType> weakTo;
	unsigned int experienceGivenIfKilled;
};

