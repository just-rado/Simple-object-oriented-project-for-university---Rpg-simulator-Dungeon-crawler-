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
	else if (data.maxHP < 0 || data.maxMP < 0)
	{
		throw std::invalid_argument("Invalid max");
	}
	else if (data.mainStats.HP < 0 || data.mainStats.MP < 0 || data.mainStats.STR < 0
		|| data.mainStats.INT < 0 || data.mainStats.AGI < 0 || data.mainStats.DEF < 0)
	{
		throw std::invalid_argument("Invalid main stats");
	}
	

}


Character& Character::operator=(const Character& other)
{
	if (this != &other)
	{
		Character temp(other);
		swap(temp);
	} // fix
	return *this;
}


const std::string& Character::getName()const
{
	return this->name;
}
int Character::getHP()const
{
	return this->mainStats.HP;
}
int Character::getMP()const
{
	return this->mainStats.MP;
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
const std::vector<StatusEffect>& Character::getStatusEffects()const
{
	return this->statusEffects;
}
unsigned int Character::getMaxHP()const
{
	return this->maxHP;
}
unsigned int Character::getMaxMP()const
{
	return this->maxMP;
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

void Character::addCharacterStatsModifiers(const CharacterStats& stats)
{
	setHP(this->mainStats.HP + stats.HP);
	setMP(this->mainStats.MP + stats.MP);
	updateMaxHP(this->maxHP + stats.HP);
	updateMaxMP(this->maxMP + stats.MP);

	setSTR(this->mainStats.STR + stats.STR);
	setINT(this->mainStats.INT + stats.INT);
	setAGI(this->mainStats.AGI + stats.AGI);
	setDEF(this->mainStats.DEF + stats.DEF);
}
void Character::removeCharacterStatsModifiers(const CharacterStats& stats)
{
	updateMaxHP(this->maxHP - stats.HP);
	updateMaxMP(this->maxMP - stats.MP);
	if (this->mainStats.HP > this->maxHP)
	{
		setHP(maxHP);
	}
	if (this->mainStats.MP > this->maxMP)
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
	if (newMaxHP > 0)
	{
		this->maxHP = newMaxHP;
	}
	else 
	{
		this->maxHP = 0;
	}
}
void  Character::updateMaxMP(unsigned int newMaxMP)
{
	if (newMaxMP > 0)
	{
		this->maxMP = newMaxMP;
	}
	else
	{
		this->maxMP = 0;
	}
}
void  Character::setGoldCoins(unsigned int newGoldCoins)
{
	this->goldCoinsOwned = newGoldCoins;
}
void  Character::setLevel(float newLevel)
{
	if (newLevel > 1)
	{
		this->currentLevel = newLevel;
	}
	else
	{
		this->currentLevel = 1;
	}
}
void Character::addNewStatusEffect(StatusEffect effect)
{
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

void Character::swap(Character& other)noexcept
{
	std::swap(this->name, other.name);
	std::swap(this->mainStats, other.mainStats);
	std::swap(this->maxHP, other.maxHP);
	std::swap(this->currentLevel, other.currentLevel);
	std::swap(this->goldCoinsOwned, other.goldCoinsOwned);
	std::swap(this->statusEffects, other.statusEffects);
	
}

