#include "Warrior.h"
#include "Item.h"
#include "Weapon.h"
#include <iostream>

Warrior::Warrior(const std::string& name) : Hero(createWarriorData(name) , Warrior::HERO_CLASS) , tauntUsed(false) , 
					remainingTurnsOfTauntEffect(0)
{
	
}


Warrior::Warrior(std::ifstream& read) : Hero(read , HERO_CLASS)
{
	read.read(reinterpret_cast<char*>(&this->tauntUsed), sizeof(this->tauntUsed));

	read.read(reinterpret_cast<char*>(&this->remainingTurnsOfTauntEffect), sizeof(this->remainingTurnsOfTauntEffect));

	if (!read)
	{
		throw std::runtime_error("error");
	}
}
void Warrior::writeToFile(std::ofstream& write)const
{
	Hero::writeOwnDataToFile(write);
	writeOwnDataToFile(write);
}
void Warrior::writeOwnDataToFile(std::ofstream& write)const
{
	write.write(reinterpret_cast<const char*>(&this->tauntUsed), sizeof(this->tauntUsed));

	write.write(reinterpret_cast<const char*>(&this->remainingTurnsOfTauntEffect), sizeof(this->remainingTurnsOfTauntEffect));

	if (!write)
	{
		throw std::runtime_error("error");
	}
}


bool Warrior::abilityTauntEnemies()
{
	if (this->tauntUsed)
	{
		std::cout << "Taunt already used\n";
		return false;
	}
	int costOfAbility = 25;
	if (costOfAbility > this->getMP())
	{
		std::cout << "Not enough mana\n";
		return false;
	}
	
	this->tauntUsed = true;
	this->remainingTurnsOfTauntEffect = 2;
	this->setMP(this->getMP() - costOfAbility);
	
	return true;
}
bool Warrior::isTauntUsed()const
{
	return this->tauntUsed;
}

void Warrior::printAbilities()const
{
	std::cout << "Abilities:\n" << "Ability 1: " << "Taunt enemies(For two turns enemies will only attack this character)\n";
}

size_t Warrior::getNumberOfAbilites()const
{
	return NUMBER_OF_ABILITIES;
}

bool Warrior::requiresATarget(size_t ability)const
{
	if (ability == 1)
	{
		return false;
	}
	return false;
}

bool Warrior::useAbility(size_t ability, Character* character)
{
	if (ability == 1)
	{
		return abilityTauntEnemies();
	}
	return false;
}

Hero* Warrior::clone()const
{
	return new Warrior(*this);
}

void Warrior::updateMainStats(int numberOfTimes)
{
	this->setSTR(this->getSTR() + 5 * numberOfTimes);
	this->setINT(this->getINT() + 1 * numberOfTimes);
	this->setAGI(this->getAGI() + 1 * numberOfTimes);

	this->updateMaxHP(this->getMaxHP() + 50 * numberOfTimes);
	this->updateMaxMP(this->getMaxMP() + 5 * numberOfTimes);

	this->setHP(this->getMaxHP());
	this->setMP(this->getMaxMP());

}

void Warrior::updateStatusOfCharacter()
{
	Character::updateStatusOfCharacter();

	if (!this->tauntUsed)
	{
		return;
	}
	
	this->remainingTurnsOfTauntEffect -= 1;
	if (this->remainingTurnsOfTauntEffect == 0)
	{
		this->tauntUsed = false;
	}
	
	
}

CharacterData Warrior::createWarriorData(const std::string& name)
{
	CharacterData data;
	data.name = name;

	data.mainStats.STR = 30;
	data.mainStats.INT = 10;
	data.mainStats.AGI = 5;
	data.mainStats.DEF = 5;

	data.maxHP = 500;
	data.maxMP = 100;
	
	
	data.mainStats.currentHP = data.maxHP;
	data.mainStats.currentMP = data.maxMP;

	data.currentLevel = 1;
	data.goldCoinsOwned = 0;
	
	data.statusEffects.clear();

	return data;
}


