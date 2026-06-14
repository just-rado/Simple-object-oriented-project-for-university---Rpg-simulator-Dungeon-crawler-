#pragma once
#include <string>
#include <vector>
#include "CharacterStats.h"
#include "DamageTypeAndEffects.h"

struct StatusEffect
{
	unsigned duration;
	StatusEffectType typeOfEffect;
};

struct CharacterData
{
	std::string name;
	CharacterStats mainStats;
	unsigned int maxHP;
	unsigned int maxMP;
	float currentLevel;
	unsigned int goldCoinsOwned;
	std::vector<StatusEffect> statusEffects;
};

class Character
{
public:
	
	const std::string& getName()const;
	const CharacterStats& getStats()const;
	float getCurrentLevel()const;
	unsigned int getGoldCoins()const;
	const std::vector<StatusEffect>& getStatusEffects()const;

protected:
	Character(const CharacterData& data);
	Character() = default;
	Character(const Character& other) = default;
	Character& operator=(const Character& other);
private:

	std::string name;
	CharacterStats mainStats;
	unsigned int maxHP;
	unsigned int maxMP;
	float currentLevel;
	unsigned int goldCoinsOwned;
	std::vector<StatusEffect> statusEffects;



};

