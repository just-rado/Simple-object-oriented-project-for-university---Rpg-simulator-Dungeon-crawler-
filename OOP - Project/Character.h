#pragma once
#include <string>
#include <vector>
#include "CharacterStats.h"
#include "DamageTypeAndEffects.h"
#include <random>
#include <fstream>

enum class TypeOfCharacter
{
	HERO,
	ENEMY,
};

#pragma pack(push , 1)
struct StatusEffect
{
	unsigned duration;
	StatusEffectType typeOfEffect;
};
#pragma pack(pop)

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
	
	Character(const CharacterData& data , TypeOfCharacter type);

	Character(std::ifstream& read);
	void writeDataToFile(std::ofstream& write)const;


	Character& operator=(const Character& other);
	virtual ~Character() = default;
	
	virtual Character* clone()const = 0;

	const std::string& getName()const;
	int getHP()const;
	int getMP()const;
	int getSTR()const;
	int getINT()const;
	int getAGI()const;
	int getDEF()const;
	unsigned int getMaxHP()const;
	unsigned int getMaxMP()const;

	const CharacterStats& getStats()const;

	TypeOfCharacter getType()const;

	float getCurrentLevel()const;
	unsigned int getGoldCoins()const;

	StatusEffect getStatusEffect(size_t index)const;
	size_t getNumberOfStatusEffects()const;

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
	void addStatusEffect(StatusEffect effect);
	void removeStatusEffect(StatusEffectType effect);

	virtual void updateStatusOfCharacter();
	
	virtual unsigned int calculateChanceOfMiss()const;
	virtual unsigned int calculateDamage()const;
	virtual unsigned int calculateDefence()const;
protected:
	static std::random_device rd;
	static std::mt19937 gen;
	void swap(Character& other)noexcept;
	virtual void updateMainStats(int numberOfTimes) = 0;

	static constexpr float STR_TO_ATTACK_DMG_MULTIPLIER = 2;
	static constexpr float INT_TO_MANA_REGEN_MULTIPLIER = 0.1f;
	static constexpr float AGI_TO_MISS_CHANCE_MULTIPLIER = 0.2f;

private:
	TypeOfCharacter type;
	std::string name;
	CharacterStats mainStats;
	unsigned int maxHP;
	unsigned int maxMP;
	float currentLevel;
	unsigned int goldCoinsOwned;
	std::vector<StatusEffect> statusEffects;

	void removeStatusEffects();
	void updateStatusEffects();
};

