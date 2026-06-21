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
	int getHP()const;
	int getMP()const;
	int getSTR()const;
	int getINT()const;
	int getAGI()const;
	int getDEF()const;
	unsigned int getMaxHP()const;
	unsigned int getMaxMP()const;

	float getCurrentLevel()const;
	unsigned int getGoldCoins()const;
	const std::vector<StatusEffect>& getStatusEffects()const;

	void setHP(int newHP);
	void setMP(int newMP);
	void setSTR(int newSTR);
	void setINT(int newINT);
	void setAGI(int newAGI);
	void setDEF(int newDEF);

	
	void addCharacterStatsModifiers(const CharacterStats& stats);
	void removeCharacterStatsModifiers(const CharacterStats& stats);
	void updateMaxHP(unsigned int newMaxHP);
	void updateMaxMP(unsigned int newMaxMP);
	void setGoldCoins(unsigned int newGoldCoins);
	void setLevel(float newLevel);
	void addNewStatusEffect(StatusEffect effect);
	void updateStatusEffects();
	

protected:
	Character(const CharacterData& data);
	Character(const Character& other) = default;
	Character& operator=(const Character& other);
	void swap(Character& other)noexcept;

	static constexpr unsigned int STR_TO_ATTACK_DMG_MULTIPLIER = 2;
	static constexpr unsigned int INT_TO_SPELL_DMG_MULTIPLIER = 1;
	static constexpr unsigned int AGI_TO_MISS_CHANCE_MULTIPLIER = 1;

private:

	std::string name;
	CharacterStats mainStats;
	unsigned int maxHP;
	unsigned int maxMP;
	float currentLevel;
	unsigned int goldCoinsOwned;
	std::vector<StatusEffect> statusEffects;
	

	
};

