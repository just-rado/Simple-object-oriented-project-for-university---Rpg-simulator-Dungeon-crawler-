#include "Warrior.h"

Warrior::Warrior(const std::string& name) : Hero(createWarriorData(name) , Warrior::heroClass) , tauntUsed(false) , 
					remainingTurnsOfTauntEffect(0)
{
	
}

void Warrior::tauntEnemies()
{
	this->tauntUsed = true;
	this->remainingTurnsOfTauntEffect = 2;
}

void Warrior::attackEnemy(const Enemy* enemy)
{
	
}

Hero* Warrior::clone()const
{
	return new Warrior(*this);
}

CharacterData Warrior::createWarriorData(const std::string& name)
{
	CharacterData data;
	data.name = name;

	data.mainStats.STR = 30;
	data.mainStats.INT = 10;
	data.mainStats.AGI = 5;
	
	data.mainStats.DEF = calculateDefence(data.mainStats);

	data.maxHP = calculateMaxHP(data.mainStats);
	data.maxMP = calculateMaxMP(data.mainStats);
	
	data.mainStats.HP = data.maxHP;
	data.mainStats.MP = data.maxMP;

	data.currentLevel = 1;
	data.goldCoinsOwned = 0;
	
	data.statusEffects.clear();

	return data;
}


unsigned int Warrior::calculateMaxHP(const CharacterStats& stats)
{
	return Warrior::BASE_HP + stats.STR * Hero::STR_TO_HEALTH_MULTIPLIER;
}
unsigned int Warrior::calculateMaxMP(const CharacterStats& stats)
{
	return Warrior::BASE_MP + stats.INT * Hero::INT_TO_MANA_MULTIPLIER;
}
unsigned int Warrior::calculateDefence(const CharacterStats& stats)
{
	return Warrior::BASE_DEFENCE + stats.AGI * Hero::AGI_TO_DEF_MULTIPLIER;
}