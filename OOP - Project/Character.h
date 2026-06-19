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
	Character(const Character& other) = default;
	Character& operator=(const Character& other);
	void swap(Character& other)noexcept;

	void setHP(int newHP);
	void setMP(int newMP);
	void setSTR(int newSTR);
	void setINT(int newINT);
	void setAGI(int newAGI);
	void setDEF(int newDEF);
private:

	std::string name;
	CharacterStats mainStats;
	unsigned int maxHP;
	unsigned int maxMP;
	float currentLevel;
	unsigned int goldCoinsOwned;
	std::vector<StatusEffect> statusEffects;
	

	
};

