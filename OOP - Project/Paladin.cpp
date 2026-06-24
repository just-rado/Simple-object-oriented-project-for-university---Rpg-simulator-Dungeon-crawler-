#include "Paladin.h"
#include <iostream>

Paladin::Paladin(const std::string& name) : Hero(createPaladinData(name) , HERO_CLASS) , Warrior(name) , Healer(name)
{

}


void Paladin::updateStatusOfCharacter()
{
	Warrior::updateStatusOfCharacter();
}

unsigned int Paladin::calculateDamage()const
{
	return Hero::calculateDamage();
}

bool Paladin::attackEnemy(Enemy* enemy)
{
	return Hero::attackEnemy(enemy);
}


void Paladin::printAbilities()const
{
	std::cout << "Abilities:\n" << "Ability 1: " << "Taunt enemies(For two turns enemies will only attack this character)\n"
		<< "Ability 2: " << "Cast a healing spell at target\n";
}
size_t Paladin::getNumberOfAbilites()const
{
	return NUMBER_OF_ABILITIES;
}
bool Paladin::requiresATarget(size_t ability)const
{
	if (ability == 1)
	{
		return false;
	}

	if (ability == 2)
	{
		return true;
	}

	return false;
}

bool Paladin::useAbility(size_t ability, Character* character)
{
	if (ability == 1)
	{
		return abilityTauntEnemies();
	}

	if (ability == 2)
	{
		if (!character)
		{
			return false;
		}

		size_t healSpell = 0;
		size_t numberOfSpells = this->getNumberOfHealSpells();
		std::cout << "Pick a healing spell to cast:\n";
		for (size_t i = 0; i < numberOfSpells; ++i)
		{
			std::cout << i << ". " << this->getHealSpell(i)->getName() << "\nDescription : " << this->getHealSpell(i)->getDescription() << '\n';
		}
		std::cin >> healSpell;

		if (healSpell >= numberOfSpells)
		{
			return false;
		}

		return abilityCastHealSpellAtCharacter(character, healSpell);
	}


	return false;
}


CharacterData Paladin::createPaladinData(const std::string& name)
{
	CharacterData data;
	data.name = name;

	data.mainStats.STR = 30;
	data.mainStats.INT = 15;
	data.mainStats.AGI = 2;
	data.mainStats.DEF = 3;

	data.maxHP = 500;
	data.maxMP = 150;


	data.mainStats.currentHP = data.maxHP;
	data.mainStats.currentMP = data.maxMP;

	data.currentLevel = 1;
	data.goldCoinsOwned = 0;

	data.statusEffects.clear();

	return data;
}


void Paladin::updateMainStats(int numberOfTimes)
{
	this->setSTR(this->getSTR() + 4 * numberOfTimes);
	this->setINT(this->getINT() + 2 * numberOfTimes);
	this->setAGI(this->getAGI() + 1 * numberOfTimes);

	this->updateMaxHP(this->getMaxHP() + 50 * numberOfTimes);
	this->updateMaxMP(this->getMaxMP() + 10 * numberOfTimes);

	this->setHP(this->getMaxHP());
	this->setMP(this->getMaxMP());
}

Hero* Paladin::clone()const
{
	return new Paladin(*this);
}