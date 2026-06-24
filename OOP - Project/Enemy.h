#pragma once
#include "Character.h"
#include "DamageTypeAndEffects.h"
#include "Hero.h"
#include "Item.h"
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
	Enemy(const CharacterData& mainStats, TypeOfEnemy type , float baseExpGiven);
	Enemy(const Enemy& other);
	Enemy& operator=(const Enemy& other) = delete;

	TypeOfEnemy getType()const;

    size_t getNumberOfWeaknesses()const;
	AugmentationType getWeakTo(size_t index)const;
	uint64_t getID()const;

	bool addWeakness(AugmentationType weakness);

	virtual const Item* itemDropped();

	float getBaseExpGainedForKilling()const;

	virtual bool attackHero(Hero* hero);
	virtual Enemy* clone()const override = 0;
protected:
	virtual void updateMainStats(int numberOfTimes)override = 0;
private:
	const uint64_t ID;
	std::vector<AugmentationType> weakTo;
	float baseExperienceGivenIfKilled;
	TypeOfEnemy enemyType;

	static uint64_t nextID;
	
	static constexpr TypeOfCharacter TYPE = TypeOfCharacter::ENEMY;
};

