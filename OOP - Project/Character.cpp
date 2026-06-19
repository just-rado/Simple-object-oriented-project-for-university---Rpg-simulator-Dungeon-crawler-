#include "Character.h"
#include <stdexcept>
Character::Character(const CharacterData& data) : name(data.name) , mainStats(data.mainStats) , maxHP(data.maxHP) , maxMP(data.maxMP),
		currentLevel(data.currentLevel), goldCoinsOwned(data.goldCoinsOwned) , statusEffects(data.statusEffects)
{
	if (name.empty())
	{
		throw std::invalid_argument("Character must have a name");
	}
	else if (currentLevel <= 0)
	{
		throw std::invalid_argument("Invalid level");
	}
	

}


Character& Character::operator=(const Character& other)
{
	if (this != &other)
	{
		Character temp(other);
		swap(temp);
	}
	return *this;
}


const std::string& Character::getName()const
{
	return this->name;
}
const CharacterStats& Character::getStats()const
{
	return this->mainStats;
}
float Character::getCurrentLevel()const
{
	return this->currentLevel;
}
unsigned int Character::getGoldCoins()const
{
	return this->goldCoinsOwned;
}
const std::vector<StatusEffect>& Character::getStatusEffects()const
{
	return this->statusEffects;
}

void Character::setHP(int newHP)
{
	if (newHP > 0)
	{
		this->mainStats.HP = newHP;
	}
	else
	{
		this->mainStats.HP = 0;
	}
	
}
void Character::setMP(int newMP)
{
	if (newMP > 0)
	{
		this->mainStats.MP = newMP;
	}
	else
	{
		this->mainStats.MP = 0;
	}
}
void Character::setSTR(int newSTR)
{
	if (newSTR > 0)
	{
		this->mainStats.STR = newSTR;
	}
	else
	{
		this->mainStats.STR = 0;
	}
}
void Character::setINT(int newINT)
{
	if (newINT > 0)
	{
		this->mainStats.INT = newINT;
	}
	else
	{
		this->mainStats.INT = 0;
	}
}
void Character::setAGI(int newAGI)
{
	if (newAGI > 0)
	{
		this->mainStats.AGI = newAGI;
	}
	else
	{
		this->mainStats.AGI = 0;
	}
}
void Character::setDEF(int newDEF)
{
	if (newDEF > 0)
	{
		this->mainStats.DEF = newDEF;
	}
	else
	{
		this->mainStats.DEF = 0;
	}
}


void Character::swap(Character& other)noexcept
{
	std::swap(this->name, other.name);
	std::swap(this->mainStats, other.mainStats);
	std::swap(this->maxHP, other.maxHP);
	std::swap(this->currentLevel, other.currentLevel);
	std::swap(this->goldCoinsOwned, other.goldCoinsOwned);
	std::swap(this->statusEffects, other.statusEffects);
	
}

