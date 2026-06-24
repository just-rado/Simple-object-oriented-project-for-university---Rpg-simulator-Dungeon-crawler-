#include "Character.h"
#include <stdexcept>

std::random_device Character::rd;
std::mt19937 Character::gen(Character::rd());

Character::Character(const CharacterData& data , TypeOfCharacter type) : name(data.name) , mainStats(data.mainStats) , maxHP(data.maxHP) , 
	maxMP(data.maxMP), currentLevel(data.currentLevel), goldCoinsOwned(data.goldCoinsOwned) , statusEffects(data.statusEffects), type(type)
{
	if (name.empty())
	{
		throw std::invalid_argument("Character must have a name");
	}
	else if (currentLevel <= 0)
	{
		throw std::invalid_argument("Invalid level");
	}
	else if (data.mainStats.currentHP < 0 || data.mainStats.currentMP < 0 || data.mainStats.STR < 0
		|| data.mainStats.INT < 0 || data.mainStats.AGI < 0 || data.mainStats.DEF < 0)
	{
		throw std::invalid_argument("Invalid main stats");
	}
	

}

Character& Character::operator=(const Character& other)
{
	if (this != &other)
	{
		std::string tempName;
		tempName.swap(this->name);

		std::vector<StatusEffect> tempVector;
		tempVector.swap(this->statusEffects);

		try
		{
			this->name = other.name;
			this->statusEffects = other.statusEffects;
		}
		catch (...)
		{
			this->name.swap(tempName);
			this->statusEffects.swap(tempVector);
			throw;
		}
		this->mainStats = other.mainStats;
		this->maxHP = other.maxHP;
		this->maxMP = other.maxMP;
		this->currentLevel = other.currentLevel;
		this->goldCoinsOwned = other.goldCoinsOwned;

		this->type = other.type;

	} 
	return *this;
}


const CharacterStats& Character::getStats()const
{
	return this->mainStats;
}

const std::string& Character::getName()const
{
	return this->name;
}
int Character::getHP()const
{
	return this->mainStats.currentHP;
}
int Character::getMP()const
{
	return this->mainStats.currentMP;
}
int Character::getSTR()const
{
	return this->mainStats.STR;
}
int Character::getINT()const
{
	return this->mainStats.INT;
}
int Character::getAGI()const
{
	return this->mainStats.AGI;
}
int Character::getDEF()const
{
	return this->mainStats.DEF;
}
float Character::getCurrentLevel()const
{
	return this->currentLevel;
}
unsigned int Character::getGoldCoins()const
{
	return this->goldCoinsOwned;
}

unsigned int Character::getMaxHP()const
{
	return this->maxHP;
}
unsigned int Character::getMaxMP()const
{
	return this->maxMP;
}

TypeOfCharacter Character::getType()const
{
	return this->type;
}

void Character::setHP(int newHP)
{
	if (newHP > this->maxHP)
	{
		this->mainStats.currentHP = this->maxHP;
	}
	else if (newHP > 0)
	{
		this->mainStats.currentHP = newHP;
	}
	else
	{
		this->mainStats.currentHP = 0;
	}
	
}
void Character::setMP(int newMP)
{
	if (newMP > this->maxMP)
	{
		this->mainStats.currentMP = this->maxMP;
	}
	else if (newMP > 0)
	{
		this->mainStats.currentMP = newMP;
	}
	else
	{
		this->mainStats.currentMP = 0;
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

void Character::addCharacterStatsModifiers(const CharacterStats& stats)
{
	updateMaxHP(this->maxHP + stats.currentHP);
	updateMaxMP(this->maxMP + stats.currentMP);

	setHP(this->mainStats.currentHP + stats.currentHP);
	setMP(this->mainStats.currentMP + stats.currentMP);
	
	setSTR(this->mainStats.STR + stats.STR);
	setINT(this->mainStats.INT + stats.INT);
	setAGI(this->mainStats.AGI + stats.AGI);
	setDEF(this->mainStats.DEF + stats.DEF);
}
void Character::removeCharacterStatsModifiers(const CharacterStats& stats)
{
	if (stats.currentHP > this->maxHP)
	{
		updateMaxHP(0);
	}
	else
	{
		updateMaxHP(this->maxHP - stats.currentHP);
	}
	
	if (stats.currentMP > this->maxMP)
	{
		updateMaxMP(0);
	}
	else
	{
		updateMaxMP(this->maxMP - stats.currentMP);
	}

	if (this->mainStats.currentHP > this->maxHP)
	{
		setHP(maxHP);
	}
	if (this->mainStats.currentMP > this->maxMP)
	{
		setMP(maxMP);
	}


	setSTR(this->mainStats.STR - stats.STR);
	setINT(this->mainStats.INT - stats.INT);
	setAGI(this->mainStats.AGI - stats.AGI);
	setDEF(this->mainStats.DEF - stats.DEF);
}

void  Character::updateMaxHP(unsigned int newMaxHP)
{
	this->maxHP = newMaxHP;
}
void  Character::updateMaxMP(unsigned int newMaxMP)
{
	this->maxMP = newMaxMP;
}
void  Character::setGoldCoins(unsigned int newGoldCoins)
{
	this->goldCoinsOwned = newGoldCoins;
}

void Character::setLevel(float newLevel)
{
	if (newLevel < this->currentLevel)
	{
		return;
	}

	int oldLevel = this->currentLevel;
	int nLevel = newLevel;
	if (nLevel > oldLevel)
	{
		this->removeStatusEffects();

		int levelsGained = nLevel - oldLevel;
		updateMainStats(levelsGained);
	}
	
	this->currentLevel = newLevel;
	
}
void Character::addStatusEffect(StatusEffect effect)
{
	if (effect.typeOfEffect == StatusEffectType::NONE)
	{
		return;
	}
	size_t size = this->statusEffects.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (this->statusEffects[i].typeOfEffect == effect.typeOfEffect)
		{
			this->statusEffects[i].duration += effect.duration;
			return;
		}
	}
	this->statusEffects.push_back(effect);
}

void Character::removeStatusEffect(StatusEffectType effect)
{
	if (effect == StatusEffectType::NONE)
	{
		return;
	}

	size_t size = this->getNumberOfStatusEffects();
	for (size_t i = 0; i < size; ++i)
	{
		if (this->statusEffects[i].typeOfEffect == effect)
		{
			this->statusEffects.erase(this->statusEffects.begin() + i);
			return;
		}
	}
}

StatusEffect Character::getStatusEffect(size_t index)const
{
	if (index >= statusEffects.size())
	{
		throw std::out_of_range("Invalid index");
	}
		
	return this->statusEffects[index];
}
size_t Character::getNumberOfStatusEffects()const
{
	return this->statusEffects.size();
}
void Character::updateStatusEffects()
{
	size_t size = this->statusEffects.size();
	for (size_t i = 0; i < size; )
	{
		this->statusEffects[i].duration -= 1;
		if (this->statusEffects[i].duration == 0)
		{
			this->statusEffects.erase(statusEffects.begin() + i);
		}
		else
		{
			++i;
		}
	}
}

void Character::removeStatusEffects()
{
	this->statusEffects.clear();
}


void Character::updateStatusOfCharacter()
{
	updateStatusEffects();
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

unsigned int Character::calculateChanceOfMiss()const
{
	return this->mainStats.AGI  * AGI_TO_MISS_CHANCE_MULTIPLIER;
}
unsigned int Character::calculateDamage()const
{
	return this->mainStats.STR * STR_TO_ATTACK_DMG_MULTIPLIER;
}
unsigned int Character::calculateDefence()const
{
	return this->mainStats.DEF;
}

