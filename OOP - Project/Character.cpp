#include "Character.h"
#include <stdexcept>
Character::Character(const CharacterData& data) : name(data.name) , mainStats(data.mainStats) , currentLevel(data.currentLevel),
		goldCoinsOwned(data.goldCoinsOwned) , statusEffects(data.statusEffects)
{
	if (name.empty())
	{
		throw std::invalid_argument("Character must have a name");
	}
	else if (currentLevel < 0)
	{
		throw std::invalid_argument("Invalid level");
	}

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